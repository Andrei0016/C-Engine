#include "Object.h"


Object::Object(std::vector<Vec3> points, std::vector<Edge3D> edges, Vec3 position, Vec3 rotationAngles, Vec3 scale): pointsV(std::move(points)), edgesV(std::move(edges)), position(position), rotationAngles(rotationAngles), scale(scale) {}

void Object::render(Window* window, CameraConfig cc) {
    std::vector<Vec3> projected;
    Mat4 modelMatrix = computeModelMatrix(this->position, this->rotationAngles, this->scale);
    Mat4 viewMatrix = computeViewMatrix(cc.cameraPos, cc.targetPos, {0, 1, 0});
    Mat4 perspectiveMatrix = createPerspectiveMatrix(cc.fovY, window->aspectRatio, cc.nearPlane, cc.farPlane);
    for (int i = 0; i < pointsV.size(); ++i) {
        projected.push_back(projectPoint(pointsV[i], modelMatrix, viewMatrix, perspectiveMatrix, window->width, window->height));
    }
    window->renderer->startFrame();
    window->renderer->clear({0, 0, 0});
    for (int i = 0; i < edgesV.size(); ++i) {
        window->renderer->drawLine(Point(edgesV[i].a), Point(edgesV[i].b), {255, 0, 0});
    }
    window->renderer->render();
    window->renderer->endFrame();
}