#include "linear_math.h"
#include "window.h"

class Object {
public:
    Vec3 position;
    Vec3 rotationAngles;
    Vec3 scale;
    Object(std::vector<Vec3> points, std::vector<Edge3D> edges, Vec3 position, Vec3 rotationAngles, Vec3 scale);
    void render(Window* window, CameraConfig cc);
private:
    std::vector<Vec3> pointsV;
    std::vector<Edge3D> edgesV;
};

