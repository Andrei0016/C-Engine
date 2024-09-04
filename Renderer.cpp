#include "Renderer.h"
#include <SDL_render.h>

Renderer::Renderer(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::startFrame() {
    commandBuffer.beginRecording();
}

void Renderer::endFrame() {
    commandBuffer.endRecording();
    commandBuffer.submit();
}

void Renderer::drawLine(Point a, Point b, RGB color) {
    commandBuffer.recordCall([=]() {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderDrawLineF(renderer, a.x, a.y, b.x, b.y);
    });
}

void Renderer::clear(RGB color) {
    commandBuffer.recordCall([=]() {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
        SDL_RenderClear(renderer);
    });
}

void Renderer::render() {
    commandBuffer.recordCall([=]() {
        SDL_RenderPresent(renderer);
    });
}
