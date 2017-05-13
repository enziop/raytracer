#include "TrackingPlane.h"


//TrackingPlane
//rectangle pointing to target with its normal and staying horizontal in respect to its upvector

//Constructors
TrackingPlane::TrackingPlane() {
    width = 1; height = 1;
    location = Vec3(0, 0, 0);
    target = Vec3(0, -1, 0);
    upVector = Vec3(0, 0, 1);
    update();
}

TrackingPlane::TrackingPlane(double _width, double _height, Vec3 _location, Vec3 _target, Vec3 _upVector) {
    width = _width; height = _height;
    location = _location;
    target = _target;
    upVector = _upVector;
    update();
}

//Update Function
void TrackingPlane::update() {
    //Vector from Plane to Target, it will become normal vector of Plane
    Vec3 normal = target - location;
    //First spanVector perpendicular to camera and upvector
    Vec3 spanX = normal.cross(upVector);
    spanX = (spanX / spanX.length()) * 0.5 * width;
    //Second spanVector perpendicular to normal and first spanVector
    Vec3 spanY = normal.cross(spanX);
    spanY = (spanY / spanY.length()) * 0.5 * height;
    
    cornerTL = location - spanY - spanX;
    cornerTR = location - spanY + spanX;
    cornerBL = location + spanY - spanX;
    cornerBR = location + spanY + spanX;
    
}

void TrackingPlane::update(Vec3 _location, Vec3 _target) {
    location = _location;
    target = _target;
    update();
}
