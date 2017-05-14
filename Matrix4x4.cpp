#include "Matrix4x4.h"

//Constructors
Matrix4x4::Matrix4x4() {}

Matrix4x4::Matrix4x4(double m[4][4]) {
    for (int iy = 0; iy < 4; ++iy) {
        for (int ix = 0; ix < 4; ++ix) {
            matrix[iy][ix] = m[iy][ix];
        }
    }
}

//operators
Matrix4x4 Matrix4x4::operator * (const Matrix4x4 &other) const {
    Matrix4x4 out;
    for (unsigned y = 0; y < 4; ++y) {
        for (unsigned x = 0; x < 4; ++x) {
            out.matrix[y][x] = 0.0;
            for (unsigned k = 0; k < 4; ++k) {
                out.matrix[x][y] += matrix[x][k] * other.matrix[k][y];
            }
        }
    }
    return out;
}

//matrix times vector
Vec3 Matrix4x4::operator * (const Vec3 &other) const {
    Vec3 out;
	double t = 1;
	double out_t = 1;
    
    out.x = matrix[0][0] * other.x + matrix[1][0] * other.y + matrix[2][0] * other.z + matrix[3][0] * t; 
    out.y = matrix[0][1] * other.x + matrix[1][1] * other.y + matrix[2][1] * other.z + matrix[3][1] * t;
    out.z = matrix[0][2] * other.x + matrix[1][2] * other.y + matrix[2][2] * other.z + matrix[3][2] * t;
    out_t = matrix[0][3] * other.x + matrix[1][3] * other.y + matrix[2][3] * other.z + matrix[3][3] * t;
    
    /* idswap
    out.x = matrix[0][0] * other.x + matrix[0][1] * other.y + matrix[0][2] * other.z + matrix[0][3] * t; 
    out.y = matrix[1][0] * other.x + matrix[1][1] * other.y + matrix[1][2] * other.z + matrix[1][3] * t;
    out.z = matrix[2][0] * other.x + matrix[2][1] * other.y + matrix[2][2] * other.z + matrix[2][3] * t;
    out_t = matrix[3][0] * other.x + matrix[3][1] * other.y + matrix[3][2] * other.z + matrix[3][3] * t;
    */
    return out;

}

Vec3 Matrix4x4::getLocation () {
        Vec3 out;
        out.x = matrix[3][0];
        out.y = matrix[3][1];
        out.z = matrix[3][2];
        return out;
}

void Matrix4x4::setLocation(const Vec3 &location) {
    matrix[3][0] = location.x;
    matrix[3][1] = location.y;
    matrix[3][2] = location.z;
}

Matrix4x4 Matrix4x4::transpose () const {
    Matrix4x4 out;
    for (uint8_t i = 0; i < 4; ++i) {
        for (uint8_t j = 0; j < 4; ++j) {
            out.matrix[i][j] = matrix[j][i];
        }
    }
    return out;
}
