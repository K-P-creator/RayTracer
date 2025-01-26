//The ray struct contains two vectors, one containing the origin coordinates and another containing the direction vector
#pragma once
#include "Vector.hpp"

struct Ray {
    Vector m_origin;
    Vector m_direction;

    Ray() { m_origin = Vector(0, 0, 0); m_direction = Vector(0, 0, 0); }
    Ray(const Vector origin, const Vector direction) { m_origin = origin; m_direction = direction; };

    Ray operator=(Ray& rhs){
        this->m_direction = rhs.m_direction; this->m_origin = rhs.m_origin;
        return *this;
    }

    Ray operator=(const Ray& rhs){
        this->m_direction = rhs.m_direction; this->m_origin = rhs.m_origin;
        return *this;
    }

};

