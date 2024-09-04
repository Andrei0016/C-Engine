#pragma once

#include <vector>

const float PI = 3.14159265358979323846264338327950288419716939937510;

struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct Vec4 {
    float x, y, z, w;

    Vec4() : x(0), y(0), z(0), w(0) {}
    Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vec4(Vec3 vect, float w) : x(vect.x), y(vect.y), z(vect.z), w(w) {}
};

struct Point {
    float x, y;
    Point(float x, float y) : x(x), y(y) {}
    Point(Vec3 vec3) : x(vec3.x), y(vec3.y) {}
};

struct Edge { Point a; Point b; };
struct Edge3D { Vec3 a; Vec3 b; };
struct Mat4 {
    float m[4][4];

    Mat4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f;  // Identity matrix
    }

    Vec3 operator*(const Vec3& v) const {
        Vec3 result;
        result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * 1.0f;
        result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * 1.0f;
        result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * 1.0f;
        return result;
    }

    Vec4 operator*(const Vec4& v) const {
        Vec4 result;
        result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
        result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
        result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
        result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
        return result;
    }


    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
};

Mat4 computeViewMatrix(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& upVector);
Mat4 createPerspectiveMatrix(float fovY, float aspectRatio, float nearPlane, float farPlane);
Mat4 computeModelMatrix(const Vec3& position, const Vec3& rotationAngles, const Vec3& scale);
void rotateObject(Vec3& rotationAngles, float angle, char axis);
Vec3 projectPoint(const Vec3& point, const Mat4& modelMatrix, const Mat4& viewMatrix, const Mat4& projectionMatrix, int screenWidth, int screenHeight);



