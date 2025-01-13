#include "Host.h"

#include <sstream>

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

    boost::interprocess::shared_memory_object::remove("SharedMemory");
}

bool Host::Init()
{
    m_window = std::make_unique<Window>("Host", 306, 781);

    if(!m_window->Init())
        return false;
 
    m_imageSize = { 306, 781 };
    m_window->SetImage("Resources\\body.bmp");
    m_window->SetRenderType(Window::RenderType::Normal);

    CreateSharedMemory();

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

void Host::CreateSharedMemory()
{
    boost::interprocess::shared_memory_object::remove("SharedMemory");

    m_managedSharedMemory = std::make_unique<boost::interprocess::managed_shared_memory>(boost::interprocess::create_only, "SharedMemory", 65536);

}

void Host::UpdateSharedMemory()
{
    if (m_managedSharedMemory->find<std::pair<int, int>>("Position").first)
        m_managedSharedMemory->destroy<std::pair<int, int>>("Position");

    if (m_managedSharedMemory->find<std::pair<int, int>>("Size").first)
        m_managedSharedMemory->destroy<std::pair<int, int>>("Size");

    std::pair<int, int>* positions = m_managedSharedMemory->construct<std::pair<int, int>>("Position")(m_windowPos);
    std::pair<int, int>* size = m_managedSharedMemory->construct<std::pair<int, int>>("Size")(m_windowSize);
}

void Host::Thread()
{
    printf("Host - starting...\n");

    while (m_running)
    {
        if (!m_window->IsRunning())
        {
            m_running = false;
            break;
        }

        m_windowPos = m_window->GetPos();
        m_windowSize = m_window->GetSize();

        UpdateSharedMemory();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    printf("Host - closing...\n");
}
