//parent class for all shapes that are drawn

#pragma once

#include "myVector.hpp"
#include "Color.hpp"
#include <vector>
#include "Ray.hpp"

using namespace std;

class Object {

    protected:
    myVector m_origin;
	Color m_color;

    //protected ctors because we dont want pure object types
    Object (myVector vec, Color col){
        m_origin = vec;
        m_color = col;
    }

    Object (){
        m_color = Color(0,0,0);
        m_origin = myVector(0,0,0);
    }

    public:

    virtual bool CheckCollision(const Ray& ray, double & pt) const = 0; // for when a t value is needed to be passed back. 
	// the t value represents that time and this is used to determine which sphere is hit first, aka closer,
	// as well as to check if a ray (which in this case behave more like lines) intersects with the sphere 
	// behind its point of origin. I use this to prevent shadows from appearing on both sides of a spehere

	virtual bool CheckCollision(const Ray& ray) const = 0; //for when no t value is needed

    virtual Color getColor(const Ray&, const double &, myVector&, myVector&, myVector&) const = 0;

    virtual ~Object() = default;

    //Getters
    const myVector& getOrigin() const {
        return this->m_origin;
    }

    const Color& getColor() const {
        return this->m_color;
    }

    //Setters
    void setOrigin(const myVector& origin){
        this->m_origin = origin;
        return;
    }

    void setColor(const Color& color){
        this->m_color = color;
        return;
    }
};