#ifndef __TriMesh_H_INCLUDED__
#define __TriMesh_H_INCLUDED__
#include "Vec3.h"
#include "Matrix4x4.h"

typedef int face[3];
struct BBox {
    double xmin, xmax, ymin, ymax, zmin, zmax;
};

class TriMesh {
private:
    BBox * bbox;
public:
    Vec3 * vertices;
    face * faces;
    int numverts;
    int numfaces;
    
    //Constructors
    TriMesh ( int _numverts, Vec3 * _vertices, int _numfaces, face * _faces);
    TriMesh ( const TriMesh &other);
    ~TriMesh ();
    
    //Getters
    Vec3 getVert ( int i);
    face * getFace ( int i);
    BBox * getBBox ();

};

#endif
