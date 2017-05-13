#include "Vec3.h"
#include <math.h>

//Constructors
Vec3::Vec3() : x(0.0), y(0.0), z(0.0){}
Vec3::Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z){}

//Functions
double Vec3::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::operator + (const Vec3 &other) const {
    Vec3 out;
    out.x = x + other.x;
    out.y = y + other.y;
    out.z = z + other.z;
    return out;
}

Vec3 Vec3::operator - (const Vec3 &other) const {
    Vec3 out;
    out.x = x - other.x;
    out.y = y - other.y;
    out.z = z - other.z;
    return out;
}

Vec3 Vec3::operator * (const double &other) const {
    Vec3 out;
    out.x = x * other;
    out.y = y * other;
    out.z = z * other;
    return out;
}

Vec3 Vec3::operator / (const double &other) const {
    Vec3 out;
    //If division by Zero, return Zero (might not be the best way to avoid errors because one does not notice if division by zero happens somewhere where it shouldn't)
    if (other > 0.0) {
        out.x = x / other;
        out.y = y / other;
        out.z = z / other;
    }
    else {
        out.x = 0.0;
        out.y = 0.0;
        out.z = 0.0;
    }
    return out;
}

double Vec3::dot(const Vec3 &other) const {
    return (x * other.x + y * other.y + z * other.z);
}

Vec3 Vec3::cross(const Vec3 &other) const {
    Vec3 out;
    out.x = (y * other.z - z * other.y);
    out.y = (z * other.x - x * other.z);
    out.z = (x * other.y - y * other.x);
    return out;
}

double Vec3::angle(Vec3 other) const {
    return std::acos(dot(other)/(length() * other.length()));
}

Vec3 Vec3::lerp(const Vec3 &other, double weight) const {
    Vec3 out;
    out.x = x + (weight * (other.x - x));
    out.y = y + (weight * (other.y - y));
    out.z = z + (weight * (other.z - z));
    return out;
}
