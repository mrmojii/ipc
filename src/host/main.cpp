#include <iostream>



//#define SDL_MAIN_HANDLED

#include "Host.h"

std::atomic<bool> g_running;

int WinMain()

//int main()
{
    Host host;
    if (host.Init())
        host.Run();

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

    return 0;
}