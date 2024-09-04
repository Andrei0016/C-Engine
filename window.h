#pragma once

#include <SDL.h>
#include "Renderer.h"

void handleEvent(SDL_Event event);

class Window {
    public:
        Renderer* renderer;
        int width, height;
        float aspectRatio;
        Window(const char* title, int w, int h);
        Window(const Window&) = delete;
        Window& operator =(const Window&) = delete;
        ~Window();

        void render();
        void line(Point a, Point b, RGB color);
        void point(Point p);
        void clear();
        bool handleEvents() const;
    private:
        SDL_Window* m_window;
        SDL_Surface* m_surface{};
        SDL_Renderer* m_renderer;
};

