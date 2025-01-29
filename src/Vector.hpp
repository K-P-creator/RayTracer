//Vector struct

#pragma once
#include <cmath>

struct Vector {
    //member variables
    double x;
    double y;
    double z;

    //default ctor
    Vector() { x = y = z = 0; }

    //paramatrized ctor
    Vector(const double a,const double b,const double c) {
    x = a; y = b; z = c;
    }

    //copy ctor
    Vector(const Vector& vector) {
        x = vector.x; y = vector.y; z = vector.z;
    }

    //member operators
    //(cross product)
    Vector operator * (Vector& rhs) {
        return Vector(x * rhs.x, y * rhs.y, z * rhs.z);
    }
    Vector& operator *= (Vector& rhs) {
        x = (x * rhs.x); y = (y * rhs.y); z = (z * rhs.z);
        return *this;
    }

    //assignment operator
    Vector operator = (const Vector& rhs) {
        x = (rhs.x); y = (rhs.y); z = (rhs.z);
        return *this;
    }

    //nonmember functions
    friend Vector operator - (const Vector& lhs, const Vector& rhs) {
        return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend bool operator != (const Vector& lhs, const Vector& rhs) {
        if (lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z)
        { return true; } else { return false; }
    }

    //dot product
    friend double Dot(Vector lhs, Vector rhs)
    {
        return(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
    }

    //normalize vector
    friend Vector Normalize(Vector vector)
    {
        double mag = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        return Vector(vector.x / mag, vector.y / mag, vector.z / mag);
    }
};
