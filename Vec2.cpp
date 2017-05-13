#include "Vec2.h"
#include <math.h>
//Constructors
Vec2::Vec2() : x(0.0), y(0.0){}
Vec2::Vec2(double _x, double _y) : x(_x), y(_y){}

//Functions
double Vec2::length() {
    return std::sqrt(x*x + y*y);
}

Vec2 Vec2::operator + (const Vec2 &other) {
    Vec2 out;
    out.x = x + other.x;
    out.y = y + other.y;
    return out;
}

Vec2 Vec2::operator - (const Vec2 &other) {
    Vec2 out;
    out.x = x - other.x;
    out.y = y - other.y;
    return out;
}

double Vec2::dot(const Vec2 &other) {
    return (x * other.x + y * other.y);
}

double Vec2::cross(const Vec2 &other) {
    return (x * other.y - y * other.x);
}

Vec2 Vec2::cross() {
    return Vec2(y, -x);
}

double Vec2::angle(Vec2 other) {
    return std::acos(dot(other)/(length() * other.length()));
}
