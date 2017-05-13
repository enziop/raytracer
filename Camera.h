#ifndef __Camera_H_INCLUDED__
#define __Camera_H_INCLUDED__
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec3.h"
#include "Matrix4x4.h"
#include "TrackingPlane.h"


class Camera {
public:
    Matrix4x4 transform;
    Vec3 direction;
    Vec3 target;
    Vec3 upVector;
    TrackingPlane viewPlane;
    //Matrix4x4 transform;
    double fov;
    int resolution_h, resolution_v;
    double image_aspect;
    
    Camera();
    Camera(const Vec3 &_location, const Vec3 &_target, const double &_fov, const int &_resolution_h, const int &_resolution_v);
    
    void update();
    void update(Vec3 _location, Vec3 _target);
    
};

#endif
