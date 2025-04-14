#pragma once

#include <vector>
#include <valarray>

constexpr float PI = 3.14159265358979323846264338327950288419716939937510;

struct Vec2 {
    float x, y;
};

struct Vec3 {
    float x, y, z;

    // Constructor
    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    // Addition
    Vec3 operator+(const Vec3& other) const {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction
    Vec3 operator-(const Vec3& other) const {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    // Scalar multiplication
    Vec3 operator*(float scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    // Scalar division
    Vec3 operator/(float scalar) const {
        if (scalar != 0.0f) {
            return Vec3(x / scalar, y / scalar, z / scalar);
        }
        return *this; // or handle divide by zero error
    }

    // Dot product
    float dot(const Vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    Vec3 cross(const Vec3& other) const {
        return Vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
        );
    }

    // Magnitude (length) of the vector
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    Vec3 normalize() const {
        float len = magnitude();
        if (len > 0.0f) {
            return *this / len;
        }
        return *this; // or handle zero length vector
    }
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
    Point(Vec2 vec2) : x(vec2.x), y(vec2.y) {}

};

struct Mat4 {
    float m[4][4] = {0.0f, 0.0f};

    Mat4(float a00, float a01, float a02, float a03,
             float a10, float a11, float a12, float a13,
             float a20, float a21, float a22, float a23,
             float a30, float a31, float a32, float a33)
    {
        m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
        m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
        m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
        m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
    }

    Mat4() {}

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
        Mat4 Ret;
        for (unsigned int i = 0 ; i < 4 ; i++) {
            for (unsigned int j = 0 ; j < 4 ; j++) {
                Ret.m[i][j] = m[i][0] * other.m[0][j] +
                              m[i][1] * other.m[1][j] +
                              m[i][2] * other.m[2][j] +
                              m[i][3] * other.m[3][j];
            }
        }

        return Ret;
    }
};

Mat4 computeViewMatrix(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& upVector);
Mat4 createPerspectiveMatrix(float width, float height, float foV, float near, float far);
Mat4 computeModelMatrix(const Vec3& position, const Vec3& rotationAngles, const Vec3& scale);
void rotateObject(Vec3& rotationAngles, float angle, char axis);
Vec2 projectToScreen(const Vec3& point, const Mat4& modelMatrix, const Mat4& viewMatrix, const Mat4& projectionMatrix, int screenWidth, int screenHeight);



