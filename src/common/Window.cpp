#include "Window.h"
#include <stdio.h>

Window::Window()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_running(false)
{

}

Window::~Window()
{

}

bool Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
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
                m_running = false;
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

        SDL_RenderSetScale(m_renderer, 1280, 720);
        SDL_SetRenderDrawColor(m_renderer, (Uint8)(colors[0] * 255), (Uint8)(colors[1] * 255), (Uint8)(colors[2] * 255), (Uint8)(colors[3] * 255));
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }
}