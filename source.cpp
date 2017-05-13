#include "source.h"


struct Ray {
    Vec3 origin;
    Vec3 direction;
};

//Viewplane Struture of 4 cornerpoints which the pixels can be interpolated between
struct viewPlane {
    Vec3 topLeft;
    Vec3 topRight;
    Vec3 botLeft;
    Vec3 botRight;
};

//simple 1D lerp function
double lerp(double a, double b, double w) {
    return a + (w * (b - a));
}
//debug printers for Vec2 and Vec3
std::string vec2str(Vec2 vec, std::string name="") {
    std::string out;
    std::stringstream tmp;
    tmp << name << "(" << vec.x << " ," << vec.y << ") L" << vec.length();
    out = tmp.str();
    return out;
}

std::string vec3str(Vec3 vec, std::string name="") {
    std::string out;
    std::stringstream tmp;
    tmp << name << "(" << vec.x << " ," << vec.y << " ," << vec.z << ") L" << vec.length();
    out = tmp.str();
    return out;
}

std::string mat4str(Matrix4x4 mat, std::string name="") {
    std::string out;
    std::stringstream tmp;
    tmp << name << "\n";
    for (unsigned y = 0; y < 4; ++y) {
        tmp << "( ";
        for (unsigned x = 0; x < 4; ++x) {
            tmp << mat.matrix[x][y] << ", ";
        }
        tmp << ")\n";
    }
    out = tmp.str();
    return out;
}

char greys[11] = " .:-=+*#%@";

int main() {
    
    //PpmIO imgout;
    //imgout.test(3200, 1800);
    
    int resolution_h = 32;
    int resolution_v = 24;
    
    Vec3 viewPlane (2, 2*(24.0/32.0), 2); //horizontal, vertical, distance to cam
    Vec3 cornerTL (-viewPlane.x / 2,-viewPlane.y / 2, 1);
    Vec3 cornerBR ( viewPlane.x / 2, viewPlane.y / 2, 1);
    
    Vec3 P1 ( 2, 0, 0);
    Vec3 P2 (-2, 0, 0);
    Vec3 P3 ( 0, 2, 0);
    Vec3 P4 ( 0,-2, 0);
    
    //put verts to mesh data class
    Vec3 * tmpVerts = new Vec3 [4] {P1, P2, P3, P4};
    face * tmpFaces = new face [2] {{0, 1, 2}, {0, 1, 3}};
    TriMesh testMesh (4, tmpVerts, 2, tmpFaces);
    delete[] tmpVerts, tmpFaces;
    std::cout << "first mesh created\n";
    //create 2nd mesh
    tmpVerts = new Vec3[8] {Vec3(-0.5,-0.5, 0.0), Vec3(-0.5, 0.5, 0.0), Vec3( 0.5, 0.5, 0.0), Vec3( 0.5,-0.5, 0.0), 
                        Vec3(-0.5,-0.5, 1.0), Vec3(-0.5, 0.5, 1.0), Vec3( 0.5, 0.5, 1.0), Vec3( 0.5,-0.5, 1.0)};
    tmpFaces = new face[12] {{0, 1, 2}, {2, 3, 0},
                        {4, 5, 6}, {6, 7, 4},
                        {0, 1, 4}, {5, 4, 0},
                        {2, 3, 7}, {7, 6, 2},
                        {3, 0, 4}, {4, 7, 3},
                        {1, 2, 6}, {6, 5, 1}};
    TriMesh cubeMesh (8, tmpVerts, 12, tmpFaces);
    delete[] tmpVerts, tmpFaces;
    std::cout << "second mesh created\n";
    TriMesh * meshList[2] = {&testMesh, &cubeMesh};
    std::cout << "mesh list fed\n";
    //initialize raytracer
    Intersector rt;
    double t;
    //initialize Camera
    Matrix4x4 camParent;
    Camera cam (Vec3(-2, -3, 1), Vec3(0, 0, 0), 90.0, resolution_h, resolution_v);
    //create transform for rotation of camera
    double rotate[4][4] = {
        {0.9961947202682495,-0.08715573698282242, 0.0, 0.0},
        {0.08715573698282242, 0.9961947202682495, 0.0, 0.0},
        { 0.0, 0.0, 1.0, 0.0},
        { 0.0, 0.0, 0.0, 1.0}};
    Matrix4x4 rotatorTM (rotate);
    //construct a grid of pixels to write renered data on
    typedef boost::multi_array<int, 2> PxGrid;
    typedef PxGrid::index PxIndex;
    PxGrid pxFrame(boost::extents[resolution_h][resolution_v]);
    
    /* raygrid to store AA rays, maybe later useful for branched path tracing but there it is maybe better to construct a tree that can be different for each pixel and store it in some abstract container, or to work recursive
    typedef boost::multi_array<Ray, 2> RayGrid;
    typedef RayGrid::index RayIndex;
    RayGrid rayFrame(boost::extents[resolution_h][resolution_v]);
    */
    
    std::cout << "starting loop\n";
    usleep(2000000);
    for (int i = 0; i < 300; ++i) {
        
        for (PxIndex y = 0; y < resolution_v; ++y) {
            for (PxIndex x = 0; x < resolution_h; ++x) {
                //construct rays for each pixel
                //interpolation is from TopLeft corner of TopLeft pixel to which corner of bottomRight pixel? need to check that, und put samples to pixel center, also need to impement anialiasing sampler (extra class)
                Vec3 scanPointLeft;
                scanPointLeft = cam.viewPlane.cornerTL.lerp(cam.viewPlane.cornerBL, double(y)/cam.resolution_v);
                Vec3 scanPointRight;
                scanPointRight = cam.viewPlane.cornerTR.lerp(cam.viewPlane.cornerBR, double(y)/cam.resolution_v);
                Vec3 planeSample;
                planeSample = scanPointLeft.lerp(scanPointRight, double(x)/cam.resolution_h);
                if (x + y == 0) {
                    std::cout << vec3str(planeSample, "lerpedTL");
                }
                if (x == resolution_h - 1 && y == resolution_v - 1) {
                    std::cout << vec3str(planeSample, "lerpedBR") << "\n";
                    //std::cout << vec3str(scanPointLeft, "scptL") << vec3str(scanPointRight, "scptR") << "w_h
                }
                Ray tmpray;
                tmpray.origin = cam.transform.getLocation();
                tmpray.direction = planeSample - tmpray.origin;
                //rayFrame[x][y] = tmpray;
                
                // clear frame
                for (int obj = 0; obj < 2; ++obj) {
                    for (int f = 0; f < meshList[obj]->numfaces; ++f) {
                        int * tmpFace = *(meshList[obj]->getFace(f));
                        pxFrame[x][y] = 0;
                    }
                }
                //render frame
                for (int obj = 0; obj < 2; ++obj) {
                    for (int f = 0; f < meshList[obj]->numfaces; ++f) {
                        int * tmpFace = *(meshList[obj]->getFace(f));
                        if (rt.triangle_intersection(meshList[obj]->getVert(tmpFace[0]), meshList[obj]->getVert(tmpFace[1]), meshList[obj]->getVert(tmpFace[2]), tmpray.origin, tmpray.direction, &t)) {
                            pxFrame[x][y] = 1; 
                            //pxFrame[x][y] = t; //z-depth kind of?
                            //Shadow tracing
                            Vec3 P = tmpray.origin + tmpray.direction * t;
                            for (int obj = 0; obj < 2; ++obj) {
                                for (int f = 0; f < meshList[obj]->numfaces; ++f) {
                                    int * tmpFace = *(meshList[obj]->getFace(f));
                                    if (rt.triangle_intersection(meshList[obj]->getVert(tmpFace[0]), meshList[obj]->getVert(tmpFace[1]), meshList[obj]->getVert(tmpFace[2]), P, Vec3(1, 1, 1), &t)) {
                                        
                                        pxFrame[x][y] = 2; //z-depth kind of?
                                    }
                                }
                            }
                            
                        }
                    }
                }
                
                
                //pxFrame[x][y] += rt.triangle_intersection(testMesh.getVert(tmpFace[0]), testMesh.getVert(tmpFace[1]), testMesh.getVert(tmpFace[2]), tmpray.origin, tmpray.direction, &t);
            }
        }
        
        std::stringstream renderview;
        for (PxIndex y = 0; y < resolution_v; ++y) {
            for (PxIndex x = 0; x < resolution_h; ++x) {
                if (pxFrame[x][y] < 10) {
                    renderview << greys[pxFrame[x][y]];
                }
                else {
                    renderview << "_";
                }
            }
            renderview << "\n";
        }
        
        //boost::this_thread::sleep(boost::posix_time::milliseconds(60));
        usleep(100000);
        std::cout << "\033[2J\033[1;1H";
        std::cout << "camRes_H: " << cam.resolution_h << " camRes_V: " << cam.resolution_v << "\n";
        std::cout << vec3str(cam.transform.getLocation(), "camLoc") << vec3str(cam.target, "camTgt") << vec3str(cam.direction, "camDir") << "\n";
        std::cout << vec3str(cam.viewPlane.location, "VPLoc") << vec3str(cam.viewPlane.target, "VPTgt") << vec3str(cam.viewPlane.upVector, "VPUp") << "\n";
        std::cout << "viewplaneW: " << cam.viewPlane.width << " viewPlaneH: " << cam.viewPlane.height << "\n";
        std::cout << vec3str(cam.viewPlane.cornerTL, "cTL") << vec3str(cam.viewPlane.cornerTR, "cTR") << vec3str(cam.viewPlane.cornerBL, "cBL") << vec3str(cam.viewPlane.cornerBR, "cBR") << "\n";
        std::cout << vec3str(P3, "P3") << "\n";
        BBox tmpBB = *(cubeMesh.getBBox());
        std::cout << "x: " << tmpBB.xmin << " " << tmpBB.xmax << " y: " << tmpBB.ymin << " " << tmpBB.ymax << " z: " << tmpBB.zmin << " " << tmpBB.zmax << "\n";
        std::cout << mat4str(camParent, "camParent");
        //std::cout << mat4str(rotatorTM, "rotatorTM");
        std::cout << mat4str(cam.transform, "CamTM");
        std::cout << renderview.str();
        renderview.str(std::string());

        camParent = camParent * rotatorTM;
        Vec3 tmpPos = Vec3(3, -4.0 + (float(i)/20), 1);
        Vec3 tmpTgt = Vec3(0, 0, 0);
        cam.update(tmpPos, tmpTgt);
        //cam.update(camParent * cam.transform.getLocation(), Vec3(0,0,0));
        
    }
    
    Vec3 origin ( 0, 0,-1);
    Vec3 dir1 ( 0, 0.5, 1);
    Vec3 dir2 ( 0,-0.5, 1);
    

    std::cout << "ray1: " << rt.triangle_intersection(P1, P2, P3, origin, dir1, &t) << " t " << t << std::endl;
    std::cout << "ray2: " << rt.triangle_intersection(P1, P2, P3, origin, dir2, &t) << " t " << t << std::endl;
    
    /*
    std::cout << vec3str(P1, "P1") << std::endl;
    std::cout << vec3str(P2, "P2") << std::endl;
    std::cout << vec3s tr(P3, "P3") << std::endl;
    
    std::cout << vec3str(P1.cross(P2), "AxB") << std::endl;
    std::cout << "P1oP2" << P1.dot(P2) << std::endl;
    std::cout << "angle P1 P2 " << P1.angle(P2) << std::endl;
    */
    
    
    return 0;
}

