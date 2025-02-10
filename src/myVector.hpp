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

    friend myVector operator + (const myVector& lhs, const myVector& rhs) {
        return myVector(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
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
        if (vector.x == 0 && vector.y == 0 && vector.z == 0){
            return vector;
        }
        double mag = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
        return myVector(vector.x / mag, vector.y / mag, vector.z / mag);
    }

    //compute distance between two vectors as if two points in 3D space
    friend double Dist(const myVector& vec1, const myVector& vec2){
        return sqrt((vec1.x-vec2.x)*(vec1.x-vec2.x)+
                    (vec1.y-vec2.y)*(vec1.y-vec2.y)+
                    (vec1.z-vec2.z)*(vec1.z-vec2.z));
    }
};
