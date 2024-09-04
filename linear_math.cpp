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
    // Compute the forward, right, and up vectors
    Vec3 forward = Vec3(
        cameraPosition.x - targetPosition.x,
        cameraPosition.y - targetPosition.y,
        cameraPosition.z - targetPosition.z
    );
    float forwardLength = std::sqrt(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
    forward = Vec3(forward.x / forwardLength, forward.y / forwardLength, forward.z / forwardLength);

    Vec3 right = Vec3(
        upVector.y * forward.z - upVector.z * forward.y,
        upVector.z * forward.x - upVector.x * forward.z,
        upVector.x * forward.y - upVector.y * forward.x
    );
    float rightLength = std::sqrt(right.x * right.x + right.y * right.y + right.z * right.z);
    right = Vec3(right.x / rightLength, right.y / rightLength, right.z / rightLength);

    Vec3 up = Vec3(
        forward.y * right.z - forward.z * right.y,
        forward.z * right.x - forward.x * right.z,
        forward.x * right.y - forward.y * right.x
    );

    // Create the View Matrix
    Mat4 viewMatrix;

    viewMatrix.m[0][0] = right.x;
    viewMatrix.m[1][0] = right.y;
    viewMatrix.m[2][0] = right.z;
    viewMatrix.m[3][0] = -(right.x * cameraPosition.x + right.y * cameraPosition.y + right.z * cameraPosition.z);

    viewMatrix.m[0][1] = up.x;
    viewMatrix.m[1][1] = up.y;
    viewMatrix.m[2][1] = up.z;
    viewMatrix.m[3][1] = -(up.x * cameraPosition.x + up.y * cameraPosition.y + up.z * cameraPosition.z);

    viewMatrix.m[0][2] = forward.x;
    viewMatrix.m[1][2] = forward.y;
    viewMatrix.m[2][2] = forward.z;
    viewMatrix.m[3][2] = -(forward.x * cameraPosition.x + forward.y * cameraPosition.y + forward.z * cameraPosition.z);

    viewMatrix.m[0][3] = 0.0f;
    viewMatrix.m[1][3] = 0.0f;
    viewMatrix.m[2][3] = 0.0f;
    viewMatrix.m[3][3] = 1.0f;

    return viewMatrix;
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

Vec3 projectPoint(const Vec3& point, const Mat4& modelMatrix, const Mat4& viewMatrix, const Mat4& projectionMatrix, int screenWidth, int screenHeight) {
    // Step 1: Transform point to world space
    Vec4 worldPoint = modelMatrix * Vec4(point, 1.0f);

    // Step 2: Transform point to camera space (optional if view matrix is identity)
    Vec4 cameraPoint = viewMatrix * worldPoint;

    // Step 3: Transform point to clip space
    Vec4 clipPoint = projectionMatrix * cameraPoint;

    // Step 4: Perform perspective division
    Vec3 ndcPoint = Vec3(clipPoint.x / clipPoint.w, clipPoint.y / clipPoint.w, clipPoint.z / clipPoint.w);

    // Step 5: Convert NDC to screen coordinates
    Vec3 screenPoint;
    screenPoint.x = (ndcPoint.x + 1.0f) * 0.5f * screenWidth;
    screenPoint.y = (1.0f - ndcPoint.y) * 0.5f * screenHeight;
    screenPoint.z = ndcPoint.z; // Optional, if you need depth information

    return screenPoint;
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
