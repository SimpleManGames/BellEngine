// Application Definition
// ----------------------

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Bell
{
    class BELL_API Application
    {
    public:
        Application();
        virtual ~Application();

        // Run loop using m_Running
        void Run();

        // Function used for window event callbacks
        // Handles event dispatching
        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in client
    Application* CreateApplication();
}

#endif // !APPLICATION_H