//The ray struct contains two myVectors, one containing the origin coordinates and another containing the direction myVector
#pragma once
#include "myVector.hpp"

struct Ray {
    myVector m_origin;
    myVector m_direction;

    //default ctor
    Ray() { m_origin = myVector(0, 0, 0); m_direction = myVector(0, 0, 0); }

    //parametrized ctor
    Ray(const myVector origin, const myVector direction) { 
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

