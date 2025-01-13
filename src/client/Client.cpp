#include "Client.h"
#include <sstream>

Client::Client()
    : m_running(false)
    , m_initialised(false)
{
}

Client::~Client()
{
    m_initialised = false;
    m_running = false;

    if (m_thread.joinable())
        m_thread.join();
}

bool Client::Init()
{
    m_window = std::make_unique<Window>("Client", 400, 200);

    if (!m_window->Init())
        return false;

    m_imageSize = { 306, 781 };
    m_window->SetImage("Resources\\skeleton.bmp");
    m_window->SetRenderType(Window::RenderType::Sized);

    m_renderConfig.posX = 0;
    m_renderConfig.posY = 0;
    m_renderConfig.sizeX = m_imageSize.first;
    m_renderConfig.sizeY = m_imageSize.second;
    m_window->SetRenderConfig(m_renderConfig);

    m_initialised = true;
    return true;
}

void Client::Run()
{
    if (!m_initialised)
        return;

    m_running = true;
    m_thread = std::thread(&Client::Thread, this);
    
    // SDL window needs to run in the main thread
    m_window->Run(); // blocking function
}

void Client::ReadHostMessage()
{
    if (m_managedSharedMemory)
        m_managedSharedMemory.reset();

    bool failedToRead = false;

    try {
        m_managedSharedMemory = std::make_unique<boost::interprocess::managed_shared_memory>(boost::interprocess::open_only, "SharedMemory");
    }
    catch(...)
    {
        failedToRead = true;
    }

    if (failedToRead)
        return;
    auto resPosition = m_managedSharedMemory->find<std::pair<int, int>>("Position");
    auto resSize = m_managedSharedMemory->find<std::pair<int, int>>("Size");

    if (resPosition.first)
        m_hostWindowPos = *resPosition.first;
    if (resSize.first)
        m_hostWindowSize = *resSize.first;

    m_managedSharedMemory->destroy<std::pair<int, int>>("Position");
    m_managedSharedMemory->destroy<std::pair<int, int>>("Size");
 
}

void Client::Thread()
{
    printf("Client - starting...\n");

    while (m_running)
    {
        if (!m_window->IsRunning())
        {
            m_running = false;
            break;
        }

        m_windowPos = m_window->GetPos();
        m_windowSize = m_window->GetSize();

        // - - get host window pos and size here using boost - -
        ReadHostMessage();
        //m_hostWindowSize = { 306 * 2, 781 };
        //m_hostWindowPos = { 900, 220 };
        // - - - - - - - - end of boost magic - - - - - - - -

        m_renderConfig.sizeX = m_hostWindowSize.first;
        m_renderConfig.sizeY = m_hostWindowSize.second;
        m_renderConfig.posX = m_hostWindowPos.first - m_windowPos.first;
        m_renderConfig.posY = m_hostWindowPos.second - m_windowPos.second;

        m_window->SetRenderConfig(m_renderConfig);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    printf("Client - closing...\n");
}
