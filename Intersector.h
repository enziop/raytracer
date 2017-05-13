#ifndef __Intersector_H_INCLUDED__
#define __Intersector_H_INCLUDED__

#include "Vec3.h"

class Intersector {
public:
int triangle_intersection( const Vec3   V1,  // Triangle vertices
    const Vec3   V2,
    const Vec3   V3,
    const Vec3    O,  //Ray origin
    const Vec3    D,  //Ray direction
    double* out );

};

#endif
