#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "boost/interprocess/managed_shared_memory.hpp"

#include "Window.h"

class Client
{
public:
    Client();
    ~Client();

    bool Init();
    void Run();
private:
    void ReadHostMessage();
    void Thread();

    bool m_initialised;
    std::atomic<bool> m_running;
    std::thread m_thread;

    std::unique_ptr<Window> m_window;
    Window::RenderConfig m_renderConfig;

    std::pair<int, int> m_imageSize;
    std::pair<int, int> m_windowSize;
    std::pair<int, int> m_windowPos;

    std::pair<int, int> m_hostWindowSize;
    std::pair<int, int> m_hostWindowPos;

    std::unique_ptr<boost::interprocess::managed_shared_memory> m_managedSharedMemory;
    boost::interprocess::managed_shared_memory::handle_t m_memoryHandle;
    void* m_messageFromHost;
};