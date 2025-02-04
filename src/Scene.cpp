#include "Scene.h"
#include "Sphere.h"
#include "Globals.h"
#include <thread>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

//alternate ctor to take in a vector of spheres
Scene::Scene(const std::vector<Sphere> &spheres) 
{
    m_count = spheres.size();
    for (const auto & sp : spheres){
        m_objects.push_back(sp);
    }
}

Color Scene::get_color(Ray& ray)
{
    Color color = m_background;
    double t = MAX_DISTANCE;
    double pt = 0;
    bool intersect = false;
    myVector intersection;
    myVector lightNorm;
    myVector intersectNorm = myVector(-1,-1,-1);

    for (int i = 0; i < m_count; i++) {
        if (m_objects[i].CheckCollision(ray, pt)) {
            if (pt < t) {
                t = pt;
                intersect = true;
                myVector intersectPt(ray.m_origin.x + t * ray.m_direction.x,
                                   ray.m_origin.y + t * ray.m_direction.y,
                                   ray.m_origin.z + t * ray.m_direction.z); //gives (x,y,z) at ray-sphere intersection, I use this to getthe orthoganal vector to the sphere

                intersection = intersectPt;

                intersectNorm = Normalize(intersectPt - m_objects[i].m_origin); //calculates the unit vector orthoganal to the intersection pt
                lightNorm = Normalize(m_light_source - intersectPt); //calculates unit vector between light source and intersect pt, these are normalized in order to make the light
                                                                     //fctr coefficient easier to calculate

                double fctr = Dot(intersectNorm, lightNorm); //gives a coefficient for color brightness based on the angle between the vector from intersect pt and the light source
                                                             //aka, surfaces on the sphere that point away from light source will have a 0 coefficient

                color = Color(trunc(m_k_amb * m_objects[i].m_color.m_red),
                              trunc(m_k_amb * m_objects[i].m_color.m_green),
                              trunc(m_k_amb * m_objects[i].m_color.m_blue)) + //calculates the ambient (no light) color of the sphere
                         Color(trunc(m_k_diff * fctr * m_objects[i].m_color.m_red),
                               trunc(m_k_diff * fctr * m_objects[i].m_color.m_green),
                               trunc(m_k_diff * fctr * m_objects[i].m_color.m_blue)); //adds the ambient color to the sphere color * fctr coeff * diffusion coeff
            }
        }
    }
    
    //checks if there are other objects between the object and light source to cast a shadow
    //this works for multiple objects, so if there are two objects casting double shadows on a point the shadow will be twice as dark
    if (t != MAX_DISTANCE && intersect) {
        for (int i = 0; i < m_count; i++) {
            //excludes the current object and checks if the light source is blocked
            Ray lightRay(intersection, lightNorm);
            double light_t = 0;

            if (m_objects[i].CheckCollision(lightRay, light_t) && light_t > 0) {
                // Object is blocking the light
                color = Color(trunc(m_k_amb * color.m_red),
                    trunc(m_k_amb * color.m_green),
                    trunc(m_k_amb * color.m_blue));
            }
        }
    }

    return color;
}

void Scene::draw()
{
    std:: ofstream out("output/out.ppm");
    out << "P3\n" << m_width << '\n' << m_height << '\n' << "255\n";

    //calculate aspect ratio for round spheres
    double aspectRatio = (1.0 * m_width) / m_height;

    for (int i = 0; i < m_height; i++) {
        for (int ii = 0; ii < m_width; ii++) {
            // Transform pixel coordinates to a 3D direction
            double x = (ii - m_width / 2.0) / m_width * aspectRatio;
            double y = (m_height / 2.0 - i) / m_height;
            myVector pixelDirection = Normalize(myVector(x, y, 1)); //camera points straight along z-axis

            // Create a ray from the viewpoint toward the pixel
            Ray ray(m_viewpoint, pixelDirection);
            out << get_color(ray);
        }
        out << "\n"; // New line after every row of pixels
    }
}

void Scene::multiThreadedDraw(){
    //number of threads to create
    size_t threadCount = thread::hardware_concurrency();

    //lines of pixels per thread
    size_t perThread = m_height/threadCount;

    //create a vector of threads
    vector <thread> threads;

    //row buffer for thread color outputs 
    vector <vector<Color>> rowBuffer(m_height);

    //calculate aspect ratio to avoid stretching
    double aspectRatio = (1.0 * m_width) / m_height;

    //Lambda implementation for threads
    //pass everything by reference and store to the buffer
    auto drawRow = [&](size_t startRow, size_t endRow){
        for (size_t i = startRow; i < endRow; i ++){
            //color temp
            vector <Color> temp(m_width);

            for (int ii = 0; ii < m_width; ii ++){
                // Transform pixel coordinates to a 3D direction
                double x = (ii - m_width / 2.0) / m_width * aspectRatio;
                double y = (m_height / 2.0 - i) / m_height;
                myVector pixelDirection = Normalize(myVector(x, y, 1)); //camera points straight along z-axis

                // Create a ray from the viewpoint toward the pixel
                Ray ray(m_viewpoint, pixelDirection);

                //store color in temp color vector
                temp[ii] = get_color(ray);
            }
            //store temp color vector in buffer
            rowBuffer[i] = temp;
        }
    };
    
    //cout << "Starting Threads...\n";
    
    //start threads
    for (size_t i = 0; i < threadCount-1; i ++){
        threads.emplace_back(drawRow, perThread*i, perThread*i + perThread);
        //cout << "   Starting " << threads[i].get_id() << endl;
    }

    //fill last thread with remainder of rows
    threads.emplace_back(drawRow, perThread*(threadCount-1), m_height);
    //cout << "   Starting " << threads[threads.size()-1].get_id() << endl;

    //cout << "Joining Threads...\n";
    
    //join threads
    for (auto& t : threads) {
        //cout << "   Joining " << t.get_id() << endl;
        t.join();
    }

    //cout << "All threads successfully joined\n";

    //set up output stream
    std:: ofstream out("output/out.ppm");
    out << "P3\n" << m_width << '\n' << m_height << '\n' << "255\n";

    //print to ppm file
    //use ' ' between vals and \n after rows for readability
    for (const auto & str : rowBuffer){
        for (int i = 0; i < m_width; i ++){
            out << str[i] << ' ';
        }
        out << endl;
    }

    //cout << "Rendering Complete. Output saved as output/out.ppm" << endl;

    return;
}