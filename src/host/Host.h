#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "Window.h"

class Host
{
public:
    Host();
    ~Host();

    bool Init();
    void Run();
private:
    void Thread();

    bool m_initialised;
    std::atomic<bool> m_running;
    std::thread m_thread;

    std::unique_ptr<Window> m_window;
};