#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "boost/interprocess/managed_shared_memory.hpp"

#include "Window.h"

class Host
{
public:
    Host();
    ~Host();

    bool Init();
    void Run();
private:
    void CreateSharedMemory();
    void UpdateSharedMemory();
    void Thread();

    bool m_initialised;
    std::atomic<bool> m_running;
    std::thread m_thread;

    std::unique_ptr<Window> m_window;

    std::pair<int, int> m_imageSize;
    std::pair<int, int> m_windowSize;
    std::pair<int, int> m_windowPos;

    std::unique_ptr<boost::interprocess::managed_shared_memory> m_managedSharedMemory;
    boost::interprocess::managed_shared_memory::size_type m_freeMemory;
    boost::interprocess::managed_shared_memory::handle_t m_memoryHandle;
    void* m_sharedMemory;
};