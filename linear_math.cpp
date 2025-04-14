#include <iostream>
#include "linear_math.h"
#include <vector>
#include "window.h"
#include <math.h>

Mat4 translationMatrix(float tx, float ty, float tz) {
    return Mat4 (1.0f, 0.0f, 0.0f, tx,
            0.0f, 1.0f, 0.0f, ty,
            0.0f, 0.0f, 1.0f, tz,
            0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 scalingMatrix(float sx, float sy, float sz) {
    return Mat4(sx, 0.0f, 0.0f, 0.0f,
            0.0f, sy, 0.0f, 0.0f,
            0.0f, 0.0f, sx, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 rotationMatrixX(float angle) {
    float rad = angle * M_PI / 180.0f;
    return Mat4(1.0f, 0.0f, 0.0f, 0.0f,
                0.0f, cos(rad), sin(rad), 0.0f,
                0.0f, sin(rad), cos(rad), 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f);
}

Mat4 rotationMatrixY(float angle) {
    float rad = angle * M_PI / 180.0f;
    return Mat4(cos(rad), 0.0f, -sin(rad), 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
                sin(rad), 0.0f, cos(rad), 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
}

Mat4 rotationMatrixZ(float angle) {
    float rad = angle * M_PI / 180.0f;
    return Mat4(cos(rad), -sin(rad), 0.0f, 0.0f,
                sin(rad), cos(rad), 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
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



Vec2 projectToScreen(const Vec3& point, const Mat4& modelMatrix, const Mat4& viewMatrix, const Mat4& projectionMatrix, int screenWidth, int screenHeight) {
    // Step 1: Local -> World
    Vec4 worldPoint = modelMatrix * Vec4(point, 1.0f);

    // Step 2: World -> Camera/View
    Vec4 viewPoint = viewMatrix * worldPoint;

    // Step 3: Camera/View -> Clip Space (after projection)
    Vec4 clipSpace = projectionMatrix * viewPoint;

    // Step 4: Perspective divide (NDC conversion)
    if (clipSpace.w != 0.0f) {
        clipSpace.x /= clipSpace.w;
        clipSpace.y /= clipSpace.w;
        clipSpace.z /= clipSpace.w;
    }

    // Step 5: NDC [-1,1] -> Screen coordinates
    float screenX = (clipSpace.x * 0.5f + 0.5f) * screenWidth;
    float screenY = (1.0f - (clipSpace.y * 0.5f + 0.5f)) * screenHeight; // Flip Y for SDL

    return Vec2(screenX, screenY);
}





Mat4 createPerspectiveMatrix(float width, float height, float fov, float near, float far) {
    float aspect = width / height;
    float f = 1.0f / tan(fov * 0.5f);
    float rangeInv = 1.0f / (near - far);

    return Mat4(
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (far + near) * rangeInv, (2 * far * near) * rangeInv,
        0.0f, 0.0f, -1.0f, 0.0f
    );
}

