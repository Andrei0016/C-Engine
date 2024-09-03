#pragma once

#include "CommandBuffer.h"
#include "game_engine.h"

class Renderer {
public:
    explicit Renderer(SDL_Renderer* renderer);
    ~Renderer();

    void startFrame();
    void endFrame();

    // Add methods for command recording
    void drawLine(Point a, Point b, RGB color);
    void clear(RGB color);
    void render();

private:
    SDL_Renderer* renderer;
    CommandBuffer commandBuffer;
};
