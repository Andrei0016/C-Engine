#include "window.h"

Window::Window(const char* title, int w, int h) {
    width = w; height = h;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) throw "Couldn't initialize SDL2!";
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    if(!m_window) throw "Couldn't create the window!";
    m_surface = SDL_GetWindowSurface(m_window);
    if(!m_surface) throw "Couldn't get the window surface!";
    m_renderer = SDL_CreateSoftwareRenderer(m_surface);
    if(!m_renderer) throw "Couldn't create the renderer!";
    SDL_RenderSetLogicalSize(m_renderer, w, h);
}

Window::~Window() {
    SDL_DestroyWindowSurface(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Window::clear() {
    SDL_RenderClear(m_renderer);
}

void Window::render() {
    SDL_UpdateWindowSurface(m_window);
    SDL_Delay(10);
}

void Window::point(Point p) {
    SDL_RenderDrawPointF(m_renderer, p.x, p.y);
}

void Window::line(Point a, Point b, RGB color) {
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLine(m_renderer, a.x, a.y, b.x, b.y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
}

