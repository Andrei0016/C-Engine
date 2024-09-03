#include "window.h"

#include <iostream>
#include <stdexcept>
#include <string>

Window::Window(const char* title, int w, int h) {
    width = w;
    height = h;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Couldn't initialize SDL2: " + std::string(SDL_GetError()));
    }

    // Create the SDL Window
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (!m_window) {
        throw std::runtime_error("Couldn't create the window: " + std::string(SDL_GetError()));
    }

    // Create the SDL Renderer
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        throw std::runtime_error("Couldn't create the renderer: " + std::string(SDL_GetError()));
    }

    // Optionally set the logical size if you want to handle resolution scaling
    SDL_RenderSetLogicalSize(m_renderer, w, h);
}

Window::~Window() {
    SDL_DestroyWindowSurface(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Window::render() {
    SDL_RenderPresent(m_renderer);
}

void Window::point(Point p) {
    SDL_RenderDrawPointF(m_renderer, p.x, p.y);
}

void Window::line(Point a, Point b, RGB color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(m_renderer, a.x, a.y, b.x, b.y);
}

bool Window::handleEvents() const {
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        std::cout << "IDK\n";
    }
    return true;
}

