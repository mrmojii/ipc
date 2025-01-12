#pragma once

#include "SDL/SDL.h"

class Window
{
public:
    Window();
    ~Window();

    bool Init();
    void Run(); // blocking function
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
};