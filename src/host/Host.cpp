#include "Host.h"



Host::Host()
    : m_running(false)
    , m_initialised(false)
{
}

Host::~Host()
{
    m_initialised = false;
    m_running = false;

    if (m_thread.joinable())
        m_thread.join();
}

bool Host::Init()
{
    m_window = std::make_unique<Window>("Host", 1280, 720);

    if(!m_window->Init())
        return false;
 
    m_initialised = true;
    return true;
}

void Host::Run()
{
    if (!m_initialised)
        return;

    m_running = true;
    m_thread = std::thread(&Host::Thread, this);

    // SDL window needs to run in the main thread
    m_window->Run(); // blocking function
}

void Host::Thread()
{
    printf("Host - starting...\n");

    while (m_running)
    {
        if (!m_window->IsRunning())
        {
            m_running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    printf("Host - closing...\n");
}
