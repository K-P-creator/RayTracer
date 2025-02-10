//definition for flat plane shape

#pragma once

#include "Object.h"
#include "myVector.hpp"
#include "Color.hpp"

class Plane : public Object {
    private:
    myVector m_normal;
    //Equation of a plane is the normal (orthogonal) vector (m_normal)
    //and a point on the plane (m_origin)

    public:
    //default ctor
    Plane() : Object {myVector(0,0,0), Color(0,0,0)} {
        this->m_normal = {0,0,0};
    }

    //parametrized ctor
    Plane(const myVector & orig, const myVector & norm, Color color) : Object {orig, color} {
        this->m_normal = norm;
    }

    ~Plane () override = default;

	//functions
	bool CheckCollision(const Ray& ray, double & pt) const override;
	bool CheckCollision(const Ray& ray) const;
    Color getColor (const Ray & ray, const double & t, myVector&, myVector&, myVector&) const override;
    const double & getSpecialVal() const override;
};