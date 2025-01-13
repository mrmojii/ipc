#include "Window.h"
#include <stdio.h>

int eventWatch(void* pthis, SDL_Event* event)
{
    if (event->type != SDL_WINDOWEVENT)
        return 1;

    if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED
        || event->window.event == SDL_WINDOWEVENT_MOVED)
    {
        Window* window = (Window*)pthis;
        SDL_RenderSetViewport(window->renderer(), NULL);
        window->Render();
    }

    return 1;
}

Window::Window(const std::string& name, int width, int height)
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_texture(nullptr)
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

    SDL_GetWindowPosition(m_window, &m_posX, &m_posY);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr)
    {
        SDL_Log("Error creating SDL_Renderer!");
        return false;
    }

    SDL_SetEventFilter((SDL_EventFilter)eventWatch, this);

    return true;
}

void Window::Run()
{
    m_running = true;

    SDL_Surface* image = SDL_LoadBMP(m_imagePath.c_str());
    m_texture = SDL_CreateTextureFromSurface(m_renderer, image);
    SDL_FreeSurface(image);

    while (m_running)
    {
        // Poll events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(m_window))
                Close();

            if (event.type == SDL_KEYDOWN)
            {
                //printf("keydown: %d - %d, mod = %d\n", event.key.keysym.scancode, event.key.keysym.sym, event.key.keysym.mod);
                if (event.key.keysym.sym == 'a')
                {
                    printf("pos:  %dx%d\nsize: %dx%d\n", m_posX, m_posY, m_width, m_height);
                }
            }
        }
        if (SDL_GetWindowFlags(m_window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }
        
        Render();
    }
}

void Window::SetImage(const std::string& path)
{
    m_imagePath = std::string(SDL_GetBasePath()) + path;
}

void Window::Close()
{
    m_running = false;

    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Window::Render()
{
    SDL_GetWindowSize(m_window, &m_width, &m_height);
    SDL_GetWindowPosition(m_window, &m_posX, &m_posY);

    float colors[] = { 0.45f, 0.55f, 0.60f, 1.00f };
    SDL_SetRenderDrawColor(m_renderer, (Uint8)(colors[0] * 255), (Uint8)(colors[1] * 255), (Uint8)(colors[2] * 255), (Uint8)(colors[3] * 255));
    SDL_RenderClear(m_renderer);

    // -- do something here --
    if (m_renderType == RenderType::Normal)
    {
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    }
    else
    {
        SDL_Rect srcrect = { 0,0,306, 200 };
        SDL_Rect dstrect = { m_renderConfig.posX, m_renderConfig.posY, m_renderConfig.sizeX, m_renderConfig.sizeY };
        int res = SDL_RenderCopy(m_renderer, m_texture, NULL, &dstrect);
    }

    // -- ----------------- --

    // End Frame
    SDL_RenderPresent(m_renderer);
}