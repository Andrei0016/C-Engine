#include <iostream>
#include "linear_math.h"

Object::Object(std::vector<Vec3> points, std::vector<Edge3D> edges)
    : pointsV(std::move(points)), edgesV(std::move(edges)) {}

Point projectPoint(const Vec3& Vec3, const CameraConfig& camera, int w, int h) {
    return {
        Vec3.x / Vec3.z * camera.focalLength + (w / 2),
        Vec3.y / Vec3.z * camera.focalLength + (w / 2)
    };
}

ObjectProjection Object::computeProjection(const CameraConfig& camera, int w, int h) {
    ObjectProjection po;
    std::vector<Point> points(pointsV.size());
    std::vector<Edge> edges(edgesV.size());
    for (size_t i = 0; i < points.size(); ++i) {
        points[i] = projectPoint(pointsV[i], camera, w, h);
    }
    for (size_t i = 0; i < edgesV.size(); ++i) {
        edges[i].a = projectPoint(edgesV[i].a, camera, w, h);
        edges[i].b = projectPoint(edgesV[i].b, camera, w, h);
    }
    po.points = points;
    po.edges = edges;

    return po;
}

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



