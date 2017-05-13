#include "TriMesh.h"
//debug includes
#include <iostream>

TriMesh::TriMesh ( int _numverts, Vec3 * _vertices, int _numfaces, face * _faces) {
    numverts = _numverts;
    numfaces = _numfaces;
    //allocate enough memory for verts
    vertices = new Vec3[numverts];
    //loop through both arrays to copy their content not just the pointer to it (deepcopy)
    for (int i = 0; i < numverts; ++i) {
        vertices[i] = _vertices[i];
    }
    std::cout << "verts copied\n";
    faces = new face[numfaces];
    for (int i = 0; i < numfaces; ++i) {
        faces[i][0] = _faces[i][0];
        faces[i][1] = _faces[i][1];
        faces[i][2] = _faces[i][2];
    }
    std::cout << "faces copied\n";
    bbox = nullptr;
}

//Constructor
TriMesh::TriMesh ( const TriMesh &other) {
    numverts = other.numverts;
    //looping through verts and faces to deepcopy them
    for (int i = 0; i < numverts; ++i) {
        vertices[i] = other.vertices[i];
    }
    numfaces = other.numfaces;
    for (int i = 0; i < numfaces; ++i) {
        //face is of type int[3], so need to deepcopy the ints instead of the pointer to first int
        faces[i][0] = other.faces[i][0];
        faces[i][1] = other.faces[i][1];
        faces[i][2] = other.faces[i][2];
    }
    bbox = nullptr;
}

//Destructor
TriMesh::~TriMesh () {
    delete vertices;
    delete faces;
    delete bbox;
}

//Getters
Vec3 TriMesh::getVert ( int i) {
    return vertices[i];
}

face * TriMesh::getFace ( int i) {
    return &(faces[i]);
}

BBox * TriMesh::getBBox() {
    //only calculate BBox if it was not already done before
    if (bbox != nullptr) {
        return bbox;
    }
    else {
        bbox = new BBox;
        bbox->xmin = bbox->xmax = vertices[0].x;
        bbox->ymin = bbox->ymax = vertices[0].y;
        bbox->zmin = bbox->zmax = vertices[0].z;
        for (int i = 1; i < numverts; ++i) {
            if (vertices[i].x < bbox->xmin) {bbox->xmin = vertices[i].x;}
            if (vertices[i].x > bbox->xmax) {bbox->xmax = vertices[i].x;}
            if (vertices[i].y < bbox->ymin) {bbox->ymin = vertices[i].y;}
            if (vertices[i].y > bbox->ymax) {bbox->ymax = vertices[i].y;}
            if (vertices[i].z < bbox->zmin) {bbox->zmin = vertices[i].z;}
            if (vertices[i].z > bbox->zmax) {bbox->zmax = vertices[i].z;}
        }
        return bbox;
    }
}
