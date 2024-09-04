#include <thread>
#include "window.h"
#include "linear_math.h"
#include "Object.h"

using namespace std;

bool running = true;

CameraConfig camera = CameraConfig({0.0f, 0.0f, -100.0f}, {0.0f, 0.0f, 0.0f}, 45.0f);
Vec3 position(0.0f, 0.0f, 10.0f);
Vec3 rotationAngles(0.0f, 0.0f, 0.0f);
Vec3 scale(1.0f, 1.0f, 1.0f);
vector<Vec3> p = { {0, 0, 0}, {0, 1, 0}, {1, 0, 0}, {0, 0, 1} };
Object obj = *new Object(p,{{0, 1}, {1, 2}, {2, 0}, {1, 3}, {2, 3}, {0, 3}}, position, rotationAngles, scale);

int main(int argc, char* args[]) {
    Window* pWindow = new Window("RENDER3D DEMO", 800, 600);
    const float cameraSpeed = 0.05f;
    while(running) {
        running = pWindow->handleEvents([=](SDL_Event event){
            char key = (char)event.key.keysym.sym;
            if (key == 'w') {
                camera.cameraPos = camera.cameraPos + camera.targetPos;
            }
            else if (key == 's') {
                camera.cameraPos = camera.cameraPos - camera.targetPos;
            }
            else if (key == 'a') {
                camera.cameraPos = camera.cameraPos + camera.targetPos.cross(Vec3(0, 1, 0)).normalize();
            }
            else if (key == 'd') {
                camera.cameraPos = camera.cameraPos - camera.targetPos.cross(Vec3(0, 1, 0)).normalize();
            }
            else if (key == 'q') {
                camera.cameraPos.y += 1;
            }
            else if (key == 'e') {
                camera.cameraPos.y -= 1;
            }
        });
        rotateObject(obj.rotationAngles, 1, 'y');
        rotateObject(obj.rotationAngles, 1, 'x');
        obj.render(pWindow, camera);
    }
    delete pWindow;
    return 0;
}

