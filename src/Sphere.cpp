#include "Sphere.h"


bool Sphere::CheckCollision(const Ray& ray, double & t)
{
    //calculates the discriminant of the sphere and the ray
    double a = Dot(ray.m_direction, ray.m_direction);
    myVector oc = (ray.m_origin - this->m_origin);
    double b = 2 * Dot(ray.m_direction, (oc));
    double c = (Dot(oc, oc) - m_radius * m_radius);
    double discrim = ((b * b) - (4.0 * a * c));
    
    //discriminants >= 0 mean that the ray intersects the sphere at some point in time
    bool intersect;
    discrim >= 0 ? intersect = true : intersect = false;

    // the t value represents that time and is passed back
    t = (-b - sqrt(discrim)) / (2 * a);
    return intersect;
}

//no t value is passed back here, same math applies as other function
bool Sphere::CheckCollision(const Ray& ray)
{
    double a = Dot(ray.m_direction, ray.m_direction);
    myVector oc = (ray.m_origin - this->m_origin);
    double b = 2 * Dot(ray.m_direction, (oc));
    double c = (Dot(oc, oc) - m_radius * m_radius);
    double discrim = ((b * b) - (4.0 * a * c));

    bool intersect;
    discrim >= 0 ? intersect = true:intersect = false;
    return intersect;
}

