//The ray struct contains two vectors, one containing the origin coordinates and another containing the direction vector
#pragma once
#include "Vector.hpp"

struct Ray {
    Vector m_origin;
    Vector m_direction;

    //default ctor
    Ray() { m_origin = Vector(0, 0, 0); m_direction = Vector(0, 0, 0); }

    //parametrized ctor
    Ray(const Vector origin, const Vector direction) { 
        m_origin = origin; 
        m_direction = direction; 
        }

    //copy ctor
    Ray (const Ray& rhs){
        *this = rhs;
    }

    Ray operator=(Ray& rhs){
        this->m_direction = rhs.m_direction; this->m_origin = rhs.m_origin;
        return (*this);
    }

    Ray operator=(const Ray& rhs){
        this->m_direction = rhs.m_direction; this->m_origin = rhs.m_origin;
        return (*this);
    }

};

