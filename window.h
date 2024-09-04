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
        bool handleEvents(const std::function<void(SDL_Event event)>& keyCallFunction) const;
    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
};

