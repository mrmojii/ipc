#pragma once

#include <atomic>
#include <string>
#include <utility>

#include "SDL/SDL.h"

class Window
{
public:
    enum class RenderType
    {
        Normal,
        Sized
    };

    struct RenderConfig
    {
        int posX;
        int posY;
        int sizeX;
        int sizeY;
    };

public:
    Window(const std::string& name, int width, int height);
    ~Window();

    bool Init();
    void Run(); // blocking function

    void SetImage(const std::string& path);

    void SetRenderType(RenderType type) { m_renderType = type; }
    void SetRenderConfig(const RenderConfig& config) { m_renderConfig = config; }

    bool IsRunning() const { return m_running; }
    void Close();

    std::pair<int, int> GetPos() const { return { m_posX, m_posY }; }
    std::pair<int, int> GetSize() const { return { m_width, m_height }; }

    void Render();

    SDL_Renderer* renderer() { return m_renderer; }
private:

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;

    std::string m_imagePath;
    std::string m_name;
    int m_width;
    int m_height;

    int m_posX;
    int m_posY;

    RenderType m_renderType;
    RenderConfig m_renderConfig;

    std::atomic<bool> m_running;
};