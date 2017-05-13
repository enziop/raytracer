#include "Intersector.h"

#define EPSILON 0.000001

/*

Möller–Trumbore ray-triangle intersection algorithm, named after its inventors Tomas Möller and Ben Trumbore

*/


int Intersector::triangle_intersection( const Vec3   V1,  // Triangle vertices
    const Vec3   V2,
    const Vec3   V3,
    const Vec3    O,  //Ray origin
    const Vec3    D,  //Ray direction
    double* out )
{
    Vec3 e1, e2;  //Edge1, Edge2
    Vec3 P, Q, T;
    double det, inv_det, u, v;
    double t;

    //Find vectors for two edges sharing V1
    e1 = V2 - V1;
    e2 = V3 - V1;
    //Begin calculating determinant - also used to calculate u parameter
    P = D.cross(e2);
    //if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
    det = e1.dot(P);
    //NOT CULLING
    if(det > -EPSILON && det < EPSILON) return 0;
    inv_det = 1.f / det;

    //calculate distance from V1 to ray origin
    T = O - V1;

    //Calculate u parameter and test bound
    u = T.dot(P) * inv_det;
    //The intersection lies outside of the triangle
    if(u < 0.f || u > 1.f) return 0;

    //Prepare to test v parameter
    Q = T.cross(e1);

    //Calculate V parameter and test bound
    v = D.dot(Q) * inv_det;
    //The intersection lies outside of the triangle
    if(v < 0.f || u + v  > 1.f) return 0;

    t = e2.dot(Q) * inv_det;

    if(t > EPSILON) { //ray intersection
        *out = t;
        return 1;
    }

    // No hit, no win
    return 0;
}
