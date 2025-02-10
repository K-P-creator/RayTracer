#include "Scene.h"
#include <thread>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

Color Scene::get_color(Ray& ray)
{
    //default color is background
    Color color = m_background;

    double t = MAX_DISTANCE;
    double pt = 0;

    bool intersect = false;

    myVector intersectPt;
    myVector lightNorm;
    myVector intersectNorm = myVector(-1,-1,-1);

    //track what object the ray hits so we can exclude it from shadow calculations
    int intersectIdx;

    
    for (int i = 0; i < m_count; i++) {
        if (m_objs[i]->CheckCollision(ray, pt)) {
            if (pt < t) {
                t = pt;
                intersect = true;

                color = m_objs[i]->getColor(ray, t, intersectPt, intersectNorm, lightNorm);
                intersectIdx = i;
            }
        }
    }
    
    //checks if there are other objects between the object and light source to cast a shadow
    //this works for multiple objects, so if there are two objects casting double shadows on
    // a point the shadow will be twice as dark

    //excluding the plane from shadow calculations because it breaks them for some reason
    if (t != MAX_DISTANCE && intersect) {
        for (int i = 0; i < m_count-1 ; i++) {

            //excludes the current object and checks if the light source is blocked
            Ray lightRay(intersectPt, lightNorm);
            double light_t = 0;

            if (m_objs[i]->CheckCollision(lightRay, light_t) && light_t > 0 && intersectIdx != i) {
                
                // Object is blocking the light, set color
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
    std::ofstream out("output/out.ppm");
    assert(out);

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

    //row buffer for thread color outputs. Reserve space for m_height # of rows
    //use indexing rather than push_back to prevent thread race conditions/save time
    vector <vector<Color>> rowBuffer(m_height);

    //calculate aspect ratio to avoid stretching
    double aspectRatio = (1.0 * m_width) / m_height;

    //Lambda implementation for threads
    //pass everything by reference and store to the buffer
    auto drawRow = [&](size_t startRow, size_t endRow){
        for (size_t i = startRow; i < endRow; i ++){
            //color temp stores all the pixels in one row... Reserve m_width number 
            //of pixels and use indexing to save time
            vector <Color> temp(m_width);

            for (int ii = 0; ii < m_width; ii ++){
                // Transform pixel coordinates to a 3D direction
                double x = (ii - m_width / 2.0) / m_width * aspectRatio;
                double y = (m_height / 2.0 - i) / m_height;
                
                //camera points straight along z-axis
                myVector pixelDirection = Normalize(myVector(x, y, 1)); 
                
                // Create a ray from the viewpoint toward the pixel
                Ray ray(m_viewpoint, pixelDirection);

                //store color in temp color vector
                temp[ii] = get_color(ray);
            }
            //store temp color vector in buffer
            rowBuffer[i] = temp;
        }
    };
    
    if (globals::debug) cout << "Starting Threads...\n";
    
    //start threads
    for (size_t i = 0; i < threadCount-1; i ++){
        threads.emplace_back(drawRow, perThread*i, perThread*i + perThread);
        if (globals::debug) cout << "   Starting " << threads[i].get_id() << endl;
    }

    //fill last thread with remainder of rows
    threads.emplace_back(drawRow, perThread*(threadCount-1), m_height);
    if (globals::debug) cout << "   Starting " << threads[threads.size()-1].get_id() << endl;

    if (globals::debug) cout << "Joining Threads...\n";
    
    //join threads
    for (auto& t : threads) {
        if (globals::debug) cout << "   Joining " << t.get_id() << endl;
        t.join();
    }

    if (globals::debug) cout << "All threads successfully joined\n";

    //set up output stream
    std:: ofstream out("output/out.ppm");
    assert(out);
    out << "P3\n" << m_width << '\n' << m_height << '\n' << "255\n";

    //print to ppm file
    //use ' ' between vals and \n after rows for readability
    for (const auto & str : rowBuffer){
        for (int i = 0; i < m_width; i ++){
            out << str[i] << ' ';
        }
        out << endl;
    }

    if (globals::debug) cout << "Rendering Complete. Output saved as output/out.ppm" << endl;

    return;
}

bool Scene::checkSphereCollision(const Sphere & sphere) const
{
    for (long long unsigned int i = 0; i < this->m_objs.size(); i ++){
        if (sphere.CheckSphereCollision(Sphere(m_objs[i]->getSpecialVal(), 
                                               m_objs[i]->getOrigin(), 
                                               m_objs[i]->getColor()))){
                                                if (globals::debug) cout << "Sphere Collision Detected!" << endl;
                                                return true;
                                               }
    }
    return false;
}
