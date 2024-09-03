#pragma once

#include <SDL.h>
#include "linear_math.h"

void handleEvent(SDL_Event event);

class Window {
    public:
        int width, height;
        Window(const char* title, int w, int h);
        Window(const Window&) = delete;
        Window& operator =(const Window&) = delete;
        ~Window();

        void render();
        void line(Point a, Point b, RGB color);
        void point(Point p);
        void clear();
    private:
        SDL_Window* m_window;
        SDL_Surface* m_surface;
        SDL_Renderer* m_renderer;
};

