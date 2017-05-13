#ifndef __Vec2_H_INCLUDED__
#define __Vec2_H_INCLUDED__

class Vec2 {
public:
    //MemberVariables
    double x, y;
    
    //Constructors
    Vec2 ();
    Vec2 (double _x, double _y);
    
    //operators
    Vec2 operator + (const Vec2 &other);
    Vec2 operator - (const Vec2 &other);
    
    double dot(const Vec2 &other);
    double cross(const Vec2 &other);
    Vec2 cross();
    double length();
    double angle(Vec2 other);
    
    //char * asString();
};

#endif
