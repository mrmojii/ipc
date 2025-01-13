#include "Window.h"
#include <stdio.h>

Window::Window(const std::string& name, int width, int height)
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_running(false)
    , m_name(name)
    , m_width(width)
    , m_height(height)
{

}

Window::~Window()
{
    Close();
}

bool Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow(m_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, window_flags);
    if (m_window == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return false;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return false;
    }

    return true;
}

void Window::Run()
{
    m_running = true;

    while (m_running)
    {
        // Poll events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window))
                Close();
        }
        if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }

        // -- do something here --

        // -- ----------------- --

        // End Frame
        float colors[] = { 0.45f, 0.55f, 0.60f, 1.00f };

        SDL_RenderSetScale(m_renderer, m_width, m_height);
        SDL_SetRenderDrawColor(m_renderer, (Uint8)(colors[0] * 255), (Uint8)(colors[1] * 255), (Uint8)(colors[2] * 255), (Uint8)(colors[3] * 255));
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
}

void Window::Close()
{
    m_running = false;

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
