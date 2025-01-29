//scenes contain objects and render constants (hight width, coefiicients etc.)

#pragma once

#include "Sphere.h"
#include <fstream>


class Scene {
private:
    int m_count; //number of objects
    Sphere* m_objects; //array of spheres (eventually i want to make the spheres a subclass of objects
                       //so that I can render planes for the background and walls 
    Vector m_light_source;
    double m_k_diff; //light diffusion coeff
    double m_k_amb; //abient light coeff
    Color m_background; //(R,B,G) oops !
    int  m_height; 
    int m_width; 
    Vector m_viewpoint;

public:
    //constructors
    Scene(int count = 0) : m_count(count),
                           m_objects(new Sphere[count]),
                           m_light_source(Vector(0,0,0)),
                           m_k_diff(0.8),
                           m_k_amb(0.2),
                           m_background(Color(0,0,0)), 
                           m_height(720),
                           m_width(1080),
                           m_viewpoint(Vector(500, 500, -1000)) {}

    Scene(const std::initializer_list<Sphere>);

    ~Scene() { delete[] m_objects; m_objects = nullptr; m_count = 0; }

    //setters
    void set_background(Color background) { m_background = background; }
    void set_light_source(Vector source) { m_light_source = source; }
    void set_k_diff(double d){ m_k_diff = d; }
    void set_k_amb(double a) { m_k_amb = a; }
    void set_height(int h)   { m_height = h; }
    void set_width(int w)    { m_width = w; }
    void set_viewpoint(Vector v) { m_viewpoint = v; }

    Color get_color(Ray& ray); //each ray represents one pixel, function returns pixel color

    //draws scene to file
    void draw();

    //threaded draw function to improve efficientcy with parallel processing
    //void multiThreadedDraw();
};