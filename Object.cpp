#include "Object.h"
#include <utility>


Object::Object(const std::vector<Vec3>& points, const std::vector<std::pair<int, int>>& edges, Vec3 position, Vec3 rotationAngles, Vec3 scale): pointsV(points), edgesV(edges), position(position), rotationAngles(rotationAngles), scale(scale) {
}

void Object::render(Window* window, CameraConfig cc) {
    Mat4 modelMatrix = computeModelMatrix(this->position, this->rotationAngles, this->scale);
    std::vector<Vec3> projected;
    Mat4 viewMatrix = computeViewMatrix(cc.cameraPos, cc.targetPos, {0, 1, 0});
    Mat4 perspectiveMatrix = createPerspectiveMatrix(cc.fovY, window->aspectRatio, cc.nearPlane, cc.farPlane);
    for (int i = 0; i < pointsV.size(); ++i) {
        projected.push_back((projectPoint(pointsV[i], modelMatrix, viewMatrix, perspectiveMatrix, window->width, window->height)));
    }
    window->renderer->startFrame();
    window->renderer->clear({0, 0, 0});
    for (auto & i : edgesV) {
        window->renderer->drawLine(Point(projected[i.first]), Point(projected[i.second]), {255, 0, 0});
    }
    window->renderer->render();
    window->renderer->endFrame();
}