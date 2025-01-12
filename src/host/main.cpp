#include <iostream>
#include <atomic>
#include "thread"

#include "boost/interprocess/mapped_region.hpp"
#include "boost/interprocess/shared_memory_object.hpp"

#define SDL_MAIN_HANDLED

#include "Window.h"

std::atomic<bool> g_running;

int main()
{
    printf("Host - starting...\n");
    Window window;
    if (window.Init())
    {
        window.Run();
    }

    /*boost::interprocess::shared_memory_object shm{
        boost::interprocess::create_only,
        "SharedMemory",
        boost::interprocess::read_write
    };

    shm.truncate(1000u);

    boost::interprocess::mapped_region region{ 
        shm,
        boost::interprocess::read_write 
    };

    memset(region.get_address(), 1, region.get_size());*/

    
    std::cout << "Host is closing...\n";
    return 0;
}