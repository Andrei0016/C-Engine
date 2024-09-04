#include <iostream>
#include <thread>
#include "window.h"
#include "linear_math.h"
#include "Object.h"

using namespace std;

bool running = true;

CameraConfig camera = CameraConfig({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 10.0f},90.0f);
Vec3 position(0.0f, 2.0f, 10.0f);
Vec3 rotationAngles(0.0f, 20.0f, 0.0f);
Vec3 scale(2.0f, 2.0f, 2.0f);
vector<Vec3> p = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1} };
vector<Edge3D> v = { {p[0], p[1]}, {p[1], p[2]}, {p[2], p[0]}, {p[1], p[3]}, {p[2], p[3]}, {p[0], p[3]} };
Object obj = *new Object(p, v, position, rotationAngles, scale);



int main(int argc, char* args[]) {
    Window* pWindow = new Window("RENDER3D DEMO", 600, 600);
    pWindow->renderer->startFrame();
    pWindow->renderer->clear({255, 0, 0});
    pWindow->renderer->render();
    pWindow->renderer->endFrame();
    SDL_Delay(100);
    while(running) {
        running = pWindow->handleEvents();
        obj.render(pWindow, camera);
    }
    delete pWindow;
    return 0;
}

