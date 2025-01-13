#include <iostream>
//#include "boost/interprocess/mapped_region.hpp"
//#include "boost/interprocess/shared_memory_object.hpp"
#define SDL_MAIN_HANDLED

#include "Client.h"

int WinMain()
//int main()
{
    Client client;
    if (client.Init())
        client.Run();
    /*boost::interprocess::shared_memory_object shm{
        boost::interprocess::open_only,
        "SharedMemory",
        boost::interprocess::read_only
    };

    boost::interprocess::mapped_region region{
        shm,
        boost::interprocess::read_only
    };

    const char* memory = (const char*)(region.get_address());

    boost::interprocess::shared_memory_object::remove("SharedMemory");

    std::cout << "Client is closing...\n";*/
    return 0;
}