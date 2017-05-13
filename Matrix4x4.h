#ifndef __Matrix4x4_H_INCLUDED__
#define __Matrix4x4_H_INCLUDED__

#include "types.h"
#include "Vec3.h"

class Matrix4x4 {
public:
    //members
    double matrix[4][4] = {
        { 1.0, 0.0, 0.0, 0.0},
        { 0.0, 1.0, 0.0, 0.0},
        { 0.0, 0.0, 1.0, 0.0},
        { 0.0, 0.0, 0.0, 1.0}};

    //constructor
    Matrix4x4();
    Matrix4x4(double m[4][4]);
    Vec3 getLocation();
    void setLocation(const Vec3 &location);
    Matrix4x4 operator * (const Matrix4x4 &other) const;
    Vec3 operator * (const Vec3 &other) const;
    Matrix4x4 transpose () const;
};

#endif
