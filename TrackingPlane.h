#ifndef __TrackingPlane_H_INCLUDED__
#define __TrackingPlane_H_INCLUDED__
#include "Vec3.h"

class TrackingPlane {

public:
    //variables given
    double width, height;
    Vec3 location;
    Vec3 target;
    Vec3 upVector;
    
    //calculated corners
    Vec3 cornerTL;
    Vec3 cornerTR;
    Vec3 cornerBL;
    Vec3 cornerBR;
    
    //constructors
    TrackingPlane();
    TrackingPlane(double _width, double _height, Vec3 _location, Vec3 _target, Vec3 _upVector = Vec3(0, 0, 1));
    
    void update();
    void update(Vec3 _location, Vec3 target);
};

#endif
