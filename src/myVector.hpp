//myVector struct
//changed name to avoid ambiguity with std::vector

#pragma once
#include <cmath>

struct myVector {
    //member variables
    double x;
    double y;
    double z;

    //default ctor
    myVector() { x = y = z = 0; }

    //paramatrized ctor
    myVector(const double a,const double b,const double c) {
    x = a; y = b; z = c;
    }

    //copy ctor
    myVector(const myVector& myVector) {
        x = myVector.x; y = myVector.y; z = myVector.z;
    }

    //member operators
    //(cross product)
    myVector operator * (myVector& rhs) {
        return myVector(x * rhs.x, y * rhs.y, z * rhs.z);
    }
    myVector& operator *= (myVector& rhs) {
        x = (x * rhs.x); y = (y * rhs.y); z = (z * rhs.z);
        return *this;
    }

    //assignment operator
    myVector operator = (const myVector& rhs) {
        x = (rhs.x); y = (rhs.y); z = (rhs.z);
        return *this;
    }

    //nonmember functions
    friend myVector operator - (const myVector& lhs, const myVector& rhs) {
        return myVector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }
    friend bool operator != (const myVector& lhs, const myVector& rhs) {
        if (lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z)
        { return true; } else { return false; }
    }

    //dot product
    friend double Dot(myVector lhs, myVector rhs)
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
    }

    //normalize myVector
    friend myVector Normalize(myVector vector)
    {
        double mag = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        return myVector(vector.x / mag, vector.y / mag, vector.z / mag);
    }
};
