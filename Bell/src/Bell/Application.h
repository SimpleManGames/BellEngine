#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Bell {

    // Base class for applications for entry point creation
    class BELL_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };


    // To be defined in client
    Application* CreateApplication();

}

// Header Guard
#endif