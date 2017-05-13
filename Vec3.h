#ifndef __Vec3_H_INCLUDED__
#define __Vec3_H_INCLUDED__

class Vec3 {
public:
    //MemberVariables
    double x, y, z;
    
    //Constructors
    Vec3 ();
    Vec3 (double _x, double _y, double _z);
    
    
    Vec3 operator + (const Vec3 &other) const;
    Vec3 operator - (const Vec3 &other) const;
    Vec3 operator * (const double &other) const;
    Vec3 operator / (const double &other) const;
    double dot(const Vec3 &other) const;
    Vec3 cross(const Vec3 &other) const;
    double length() const;
    double angle(Vec3 other) const;
    Vec3 lerp(const Vec3 &other, double weight) const;
    
};

#endif
