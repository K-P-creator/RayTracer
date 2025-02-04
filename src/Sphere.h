//Sphere struct
#pragma once
#include "Ray.hpp"
#include "Color.hpp"

struct Sphere {
	//member variables
	double m_radius;
	myVector m_origin;
	Color m_color;


	//default ctor
	Sphere() {
		this->m_radius = 0;
		this->m_origin = myVector(0,0,0);
		this->m_color = Color(0, 0, 0);
	}

	//par ctor
	Sphere(double radius, myVector origin, Color color) {
		this->m_origin = origin;
		this->m_radius = radius;
		this->m_color = color;
	}

	//copy ctor
	Sphere(const Sphere & sphere) {
		this->m_origin = sphere.m_origin;
		this->m_radius = sphere.m_radius;
		this->m_color = sphere.m_color;
	}

	//functions
	bool CheckCollision(const Ray& ray, double & pt); // for when a t value is needed to be passed back. 
	// the t value represents that time and this is used to determine which sphere is hit first, aka closer,
	// as well as to check if a ray (which in this case behave more like lines) intersects with the sphere 
	// behind its point of origin. I use this to prevent shadows from appearing on both sides of a spehere

	bool CheckCollision(const Ray& ray); //for when no t value is needed

};