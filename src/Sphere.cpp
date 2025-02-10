#include "Sphere.h"

bool Sphere::CheckCollision(const Ray& ray, double & t) const
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
bool Sphere::CheckCollision(const Ray& ray) const
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

Color Sphere::getColor(const Ray &ray, const double & t, myVector & intersectPt,
                       myVector & intersectNorm, myVector & lightNorm) const{
    
    Color color(SCENE_BACKGROUND);
    

    //give(x,y,z) at ray-sphere intersection, I use this to get
    //the orthoganal vector to the sphere
    intersectPt = myVector(ray.m_origin.x + t * ray.m_direction.x,
                                    ray.m_origin.y + t * ray.m_direction.y,
                                    ray.m_origin.z + t * ray.m_direction.z); 


    //calculates the unit vector orthoganal to the intersection pt
    intersectNorm = Normalize(intersectPt - m_origin); 


    //calculates unit vector between light source and intersect pt, 
    //these are normalized in order to make the light
    //fctr coefficient easier to calculate
    lightNorm = Normalize(myVector(SCENE_LIGHT_SRC) - intersectPt); 
    

    //a coefficient for color brightness based on the angle between the vector from 
    //intersect pt and the light source aka, surfaces on the sphere that point away from 
    //light source will have a 0 coefficient
    double fctr = Dot(intersectNorm, lightNorm); 
    
    
    //calculates the ambient (no light) color of the sphere
    color = Color(trunc(SCENE_K_AMB * m_color.m_red),
                  trunc(SCENE_K_AMB * m_color.m_green),
                  trunc(SCENE_K_AMB * m_color.m_blue)) + 
    //add the ambient color to the sphere color * fctr coeff * diffusion coeff
             Color(trunc(SCENE_K_DIFF * fctr * m_color.m_red),
                   trunc(SCENE_K_DIFF * fctr * m_color.m_green),
                   trunc(SCENE_K_DIFF * fctr * m_color.m_blue));

    
    return color;
}

bool Sphere::CheckSphereCollision(const Sphere & sphere) const
{
    if (Dist(this->m_origin, sphere.m_origin) < (this->m_radius + sphere.m_radius)){
        return true;
    }else{
        return false;
    }
}

const double &Sphere::getSpecialVal() const
{
    return m_radius;
}
