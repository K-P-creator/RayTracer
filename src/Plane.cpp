#include "Plane.h"
#include <iostream>
#include "Globals.h"

bool Plane::CheckCollision(const Ray& ray, double & pt) const{
    //start with the plane normal Pn (make sure to normalize it)
    // use t = ((Po - Ro) dot Pn) / (Rd dot Pn)
    myVector norm = Normalize (this->m_normal);
    pt = (Dot( (this->m_origin - ray.m_origin), norm) / (Dot(ray.m_direction, norm)));

    if (pt <= 0) return false;

    return true;
}

bool Plane::CheckCollision(const Ray& ray) const{
    //start with the plane normal Pn (make sure to normalize it)
    // use t = ((Po - Ro) dot Pn) / (Rd dot Pn)
    myVector norm = Normalize (this->m_normal);
    if (Dot( (this->m_origin - ray.m_origin), norm) / (Dot(ray.m_direction, norm)) <= 0) return false;

    return true;
}

Color Plane::getColor(const Ray &ray, const double & t, myVector & intersectPt, myVector & intersectNorm, myVector & lightNorm) const
{   
    //set the intersect point to be passed back
    //the vectors passed by ref are needed for the shadow calculations in scene.cpp
    //Pint = Ro + t Rd
    intersectPt = ray.m_origin + (myVector(ray.m_direction.x * t, ray.m_direction.y * t, ray.m_direction.z * t));

    //calculates the unit vector orthoganal to the intersection pt
    intersectNorm = Normalize(intersectPt - m_origin);

    //calculates unit vector between light source and intersect pt, 
    //these are normalized in order to make the light
    //fctr coefficient easier to calculate
    lightNorm = Normalize(myVector(SCENE_LIGHT_SRC) - intersectPt); 

    return this->m_color;
}
