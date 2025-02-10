//scenes contain objects and render constants (hight width, coefiicients etc.)

#pragma once

#include "Object.h"
#include "Sphere.h"
#include "Color.hpp"
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

class Scene {
private:
    int m_count; //number of objects
    vector<shared_ptr<Object>> m_objs; //array of objects
    myVector m_light_source;
    double m_k_diff; //light diffusion coeff
    double m_k_amb; //abient light coeff
    Color m_background; //(R,B,G) oops !
    int  m_height; 
    int m_width; 
    myVector m_viewpoint;

public:
    //constructors
    Scene(int count = 0) : m_count(count),
                           m_light_source(myVector(0,0,0)),
                           m_k_diff(0.8),
                           m_k_amb(0.2),
                           m_background(Color(0,0,0)), 
                           m_height(720),
                           m_width(1080),
                           m_viewpoint(myVector(500, 500, -1000)) {}

    //alternate ctor to take in vector of objects
    //alternate ctor to take in a vector of spheres
    Scene(const vector<shared_ptr<Object>>& objs) 
    {
        m_count = objs.size();

        for (const auto& sp : objs){
            m_objs.emplace_back(sp);
        }
    }

        ~Scene() { }

    //setters
    void set_background(Color background) { m_background = background; }
    void set_light_source(myVector source) { m_light_source = source; }
    void set_k_diff(double d){ m_k_diff = d; }
    void set_k_amb(double a) { m_k_amb = a; }
    void set_height(int h)   { m_height = h; }
    void set_width(int w)    { m_width = w; }
    void set_viewpoint(myVector v) { m_viewpoint = v; }

    Color get_color(Ray& ray); //each ray represents one pixel, function returns pixel color

    //draws scene to file
    void draw();

    //threaded draw function to improve efficientcy with parallel processing
    void multiThreadedDraw();

    //check if sphere intersects with any other spheres in scene
    //I only use this for drawing when there are no other object subclasses
    //initialized in side the object list. This wont work if there are other shapes in there
    //it is purely for random sphere generation
    bool checkSphereCollision(const Sphere &) const;
};