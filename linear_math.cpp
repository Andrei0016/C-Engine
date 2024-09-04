#include <iostream>
#include "linear_math.h"
#include <vector>
#include "window.h"
#include <math.h>

Mat4 translationMatrix(float tx, float ty, float tz) {
    Mat4 mat;
    mat.m[0][3] = tx;
    mat.m[1][3] = ty;
    mat.m[2][3] = tz;
    return mat;
}

Mat4 scalingMatrix(float sx, float sy, float sz) {
    Mat4 mat;
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    return mat;
}

Mat4 rotationMatrixX(float angle) {
    Mat4 mat;
    float rad = angle * M_PI / 180.0f;
    mat.m[1][1] = cos(rad);
    mat.m[1][2] = -sin(rad);
    mat.m[2][1] = sin(rad);
    mat.m[2][2] = cos(rad);
    return mat;
}

Mat4 rotationMatrixY(float angle) {
    Mat4 mat;
    float rad = angle * M_PI / 180.0f;
    mat.m[0][0] = cos(rad);
    mat.m[0][2] = sin(rad);
    mat.m[2][0] = -sin(rad);
    mat.m[2][2] = cos(rad);
    return mat;
}

Mat4 rotationMatrixZ(float angle) {
    Mat4 mat;
    float rad = angle * M_PI / 180.0f;
    mat.m[0][0] = cos(rad);
    mat.m[0][1] = -sin(rad);
    mat.m[1][0] = sin(rad);
    mat.m[1][1] = cos(rad);
    return mat;
}

void rotateObject(Vec3& rotationAngles, float angle, char axis) {
    switch (axis) {
        case 'x':
            rotationAngles.x += angle;
            break;
        case 'y':
            rotationAngles.y += angle;
            break;
        case 'z':
            rotationAngles.z += angle;
            break;
        default:
            std::cerr << "Invalid axis! Use 'x', 'y', or 'z'.\n";
    }
}

Mat4 computeModelMatrix(const Vec3& position, const Vec3& rotationAngles, const Vec3& scale) {
    Mat4 translate = translationMatrix(position.x, position.y, position.z);
    Mat4 rotateX = rotationMatrixX(rotationAngles.x);
    Mat4 rotateY = rotationMatrixY(rotationAngles.y);
    Mat4 rotateZ = rotationMatrixZ(rotationAngles.z);
    Mat4 scaleMat = scalingMatrix(scale.x, scale.y, scale.z);

    Mat4 rotationMatrix = rotateZ * rotateY * rotateX;
    Mat4 modelMatrix = translate * rotationMatrix * scaleMat;

    return modelMatrix;
}

Mat4 computeViewMatrix(const Vec3& cameraPosition, const Vec3& targetPosition, const Vec3& upVector) {
    Vec3 forward = (targetPosition - cameraPosition).normalize();
    Vec3 right = upVector.cross(forward).normalize();
    Vec3 up = forward.cross(right);

    Mat4 viewMatrix;
    viewMatrix.m[0][0] = right.x; viewMatrix.m[0][1] = up.x; viewMatrix.m[0][2] = -forward.x; viewMatrix.m[0][3] = 0.0f;
    viewMatrix.m[1][0] = right.y; viewMatrix.m[1][1] = up.y; viewMatrix.m[1][2] = -forward.y; viewMatrix.m[1][3] = 0.0f;
    viewMatrix.m[2][0] = right.z; viewMatrix.m[2][1] = up.z; viewMatrix.m[2][2] = -forward.z; viewMatrix.m[2][3] = 0.0f;
    viewMatrix.m[3][0] = -right.dot(cameraPosition); viewMatrix.m[3][1] = -up.dot(cameraPosition); viewMatrix.m[3][2] = forward.dot(cameraPosition); viewMatrix.m[3][3] = 1.0f;

    return viewMatrix;
}



Vec3 projectPoint(const Vec3& point, const Mat4& modelMatrix, const Mat4& viewMatrix, const Mat4& projectionMatrix, int screenWidth, int screenHeight) {
    Vec4 worldPoint = modelMatrix * Vec4(point, 1.0f);
    Vec4 cameraPoint = viewMatrix * worldPoint;
    Vec4 clipPoint = projectionMatrix * cameraPoint;

    // Handle potential division by zero in perspective division
    if (std::abs(clipPoint.w) > 1e-5) {
        Vec3 ndcPoint(clipPoint.x / clipPoint.w, clipPoint.y / clipPoint.w, clipPoint.z / clipPoint.w);
        Vec3 screenPoint;
        screenPoint.x = (ndcPoint.x + 1.0f) * 0.5f * screenWidth;
        screenPoint.y = (1.0f - ndcPoint.y) * 0.5f * screenHeight;
        screenPoint.z = ndcPoint.z;
        return screenPoint;
    } else {
        // Return an invalid screen point or handle the case differently
        return Vec3(-1.0f, -1.0f, -1.0f); // Example: returns invalid coordinates
    }
}


Mat4 createPerspectiveMatrix(float fovY, float aspectRatio, float nearPlane, float farPlane) {
    float f = 1.0f / tanf(fovY / 2.0f);
    Mat4 result = Mat4();

    result.m[0][0] = f / aspectRatio;
    result.m[1][1] = f;
    result.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    result.m[2][3] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
    result.m[3][2] = -1.0f;
    result.m[3][3] = 0.0f;

    return result;
}
