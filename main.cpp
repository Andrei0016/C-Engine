#include <iostream>
#include <unistd.h>
#include "window.h"
#include "linear_math.h"

using namespace std;

std::vector<Vec3> transformPoints(const std::vector<Vec3>& points, const Mat4& modelMatrix) {
    std::vector<Vec3> transformedPoints;
    for (const Vec3& point : points) {
        transformedPoints.push_back(modelMatrix * point);
    }
    return transformedPoints;
}

int main(int argc, char* args[]) {
    Window* pWindow = new Window("RENDER3D DEMO", 600, 600);
    CameraConfig camera = { 0, 0, 100 };
    Vec3 position(0.0f, 2.0f, 3.0f);
    Vec3 rotationAngles(0.0f, 20.0f, 0.0f);  // Renamed from 'rotation' to 'rotationAngles'
    Vec3 scale(2.0f, 2.0f, 2.0f);
    vector<Vec3> p = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1} };

    SDL_Event evt;
    bool programrunning = true;
    int a = 1;
    while(programrunning)
    {
        pWindow->clear();
//        SDL_WaitEvent(&evt);
//        if(evt.type == SDL_QUIT)
//            programrunning = false;
        rotateObject(rotationAngles, 10.0f, 'x');
        Mat4 modelMatrix = computeModelMatrix(position, rotationAngles, scale);
        vector<Vec3> pa = transformPoints(p, modelMatrix);
        vector<Edge3D> v = { {pa[0], pa[1]}, {pa[1], pa[2]}, {pa[2], pa[0]}, {pa[1], pa[3]}, {pa[2], pa[3]}, {pa[0], pa[3]} };
        Object obj = *new Object(pa, v);
        ObjectProjection objP = obj.computeProjection(camera, 600, 600);
        for (int i = 0; i < objP.edges.size(); ++i) {
            pWindow->line(objP.edges[i].a, objP.edges[i].b, RGB { 255, 255, 255 });
        }
        pWindow->render();
        sleep(1);
    }

    delete pWindow;
    return 0;
}

