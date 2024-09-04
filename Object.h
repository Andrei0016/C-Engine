#include "window.h"

class Object {
public:
    Vec3 position;
    Vec3 rotationAngles;
    Vec3 scale;
    Object(const std::vector<Vec3>& points, const std::vector<std::pair<int, int>>& edges, Vec3 position, Vec3 rotationAngles, Vec3 scale);
    void render(Window* window, CameraConfig cc);
private:
    std::vector<Vec3> pointsV;
    std::vector<std::pair<int, int>> edgesV;
};

