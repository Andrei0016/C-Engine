#pragma once

#include <stdint.h>
#include "linear_math.h"

struct CameraConfig {
    Vec3 cameraPos;
    Vec3 targetPos;
    float fovY;
    float nearPlane = 0.1f;
    float farPlane = 10000.0f;
    CameraConfig(Vec3 cameraPos, Vec3 targetPos, float fovY, float nearPlane, float farPlane): cameraPos(cameraPos), targetPos(targetPos), fovY(fovY * (M_PI / 180.0f)), nearPlane(nearPlane), farPlane(farPlane){}
    CameraConfig(Vec3 cameraPos, Vec3 targetPos, float fovY): cameraPos(cameraPos), targetPos(targetPos), fovY(fovY * (M_PI / 180.0f)){}
};

struct RGB { uint8_t r, g, b; };

