#include "Scene.h"
#include "Sphere.h"
#include "Globals.h"


Scene::Scene(const std::initializer_list<Sphere> init)
{
    m_objects = new Sphere[init.size()];
    m_count = init.size();
    std::copy(init.begin(), init.end(), m_objects);
    m_k_diff = 0.8;
    m_k_amb = 0.5;
    m_height = 720,
    m_width = 1080,
    m_viewpoint = Vector(500, 500, -1000);
}

Color Scene::get_color(Ray& ray)
{
    Color color = m_background;
    double t = MAX_DISTANCE;
    double pt = 0;
    bool intersect = false;
    Vector intersection;
    Vector lightNorm;
    Vector intersectNorm = Vector(-1,-1,-1);

    for (int i = 0; i < m_count; i++) {
        if (m_objects[i].CheckCollision(ray, pt)) {
            if (pt < t) {
                t = pt;
                intersect = true;
                Vector intersectPt(ray.m_origin.x + t * ray.m_direction.x,
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
            Vector pixelDirection = Normalize(Vector(x, y, 1)); //camera points straight along z-axis

            // Create a ray from the viewpoint toward the pixel
            Ray ray(m_viewpoint, pixelDirection);
            out << get_color(ray);
        }
        out << "\n"; // New line after every row of pixels
    }
}

//multi threaded draw fucntion
/*
void Scene::multiThreadedDraw()
{
    //open output doc and format
    std::ofstream out("output/out.ppm");
    out << "P3\n" << m_width << '\n' << m_height << '\n' << "255\n";
    
    //calculate number of rays for work allocation
    size_t rayCount = SCENE_HEIGHT * SCENE_WIDTH;

    //obtain thread count from hardware
    size_t threadCount = std::thread::hardware_concurrency();

    //calculate workload per thread
    size_t workLoad = rayCount / threadCount;

    //calculate aspect ratio to prevent stretching
    double aspectRatio = (1.0 * m_width) / m_height;

    //create threads
    std::thread* threadList;
    threadList = new std::thread[threadCount];

    for (int i = 0; i < SCENE_HEIGHT; i ++) {
        for (int ii = 0; i < SCENE_WIDTH; ii++) {
            for (int thdidx = 0; thdidx < threadCount; thdidx++) {

            }
        }
    }

}
*/

