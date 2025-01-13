#pragma once

#include <atomic>
#include <string>

#include "SDL/SDL.h"

class Window
{
public:
    Window(const std::string& name, int width, int height);
    ~Window();

    bool Init();
    void Run(); // blocking function

    bool IsRunning() const { return m_running; }
    void Close();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    std::string m_name;
    int m_width;
    int m_height;

    std::atomic<bool> m_running;
};