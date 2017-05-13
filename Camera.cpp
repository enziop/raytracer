#include "Camera.h"



//Camera

//Constructors

Camera::Camera() {
    Camera(Vec3(0,-1, 1), Vec3(0, 0, 1), 90.0, 64, 32);
}
Camera::Camera(const Vec3 &_location, const Vec3 &_target, const double &_fov, const int &_resolution_h, const int &_resolution_v) {
    transform.setLocation(_location);
    target = _target;
    upVector = Vec3(0, 0, 1);
    direction = (target - transform.getLocation());
    direction = direction / direction.length();
    fov = _fov;
    resolution_h = _resolution_h;
    resolution_v = _resolution_v;
    image_aspect = double(resolution_h) / resolution_v;
    double width = std::tan((fov/360.0)*M_PI);
    viewPlane = TrackingPlane(width, width/image_aspect, transform.getLocation() + direction , transform.getLocation(), upVector);
}

void Camera::update() {
    viewPlane.update(transform.getLocation() - direction, transform.getLocation());
}
void Camera::update(Vec3 _location, Vec3 _target) {
    transform.setLocation(_location);
    target = _target;
    direction = target - transform.getLocation();
    direction = direction / direction.length();
    viewPlane.update(transform.getLocation() + direction, transform.getLocation());
}
