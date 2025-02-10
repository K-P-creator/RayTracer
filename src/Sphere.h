//Sphere struct
#pragma once
#include "Object.h"

class Sphere : public Object {
	//member variables
	private:
	double m_radius;

	public:
	//default ctor
	Sphere() : Object {myVector(0,0,0), Color(0, 0, 0)} {
		this->m_radius = 0;
	}

	//par ctor
	Sphere(const double & radius, const myVector& origin, const Color& color) : Object {origin, color} {
		this->m_radius = radius;
	}

	//copy ctor
	Sphere(const Sphere & sphere) : Object {sphere.m_origin, sphere.m_color} {
		this->m_radius = sphere.m_radius;
	}

	~Sphere () override  = default;

	//functions
	bool CheckCollision(const Ray& ray, double & pt) const override;
	bool CheckCollision(const Ray& ray) const;
	Color getColor (const Ray & ray, const double & t, myVector&, myVector&, myVector&) const override;
	
	//returns true if spheres intersect with one another
	//I'll use this for drawing random scenes without intersecting spheres
	bool CheckSphereCollision(const Sphere &) const;

	//return the radius
	const double & getSpecialVal() const override;
};