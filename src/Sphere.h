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
	Sphere(double& radius, myVector& origin, Color& color) : Object {origin, color} {
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
};