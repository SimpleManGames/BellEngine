// Application Definition
// ----------------------

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "Events/Event.h"
#include "Bell/Layer/LayerStack.h"
#include "Events/ApplicationEvent.h"

#include "Bell/Base/Time.h"

#include "Bell/ImGui/ImGuiLayer.h"

namespace Bell
{
    /**
     * @brief State enum for keeping track of the current process of the Application
     * 
     */
    enum class ApplicationState
    {
        Invalid,
        Constructing,
        Initializing,
        Running,
        Minimized,
        ShuttingDown,
        Destroying
    };

    /**
     * @brief Controls Initialization of the Application as
     * well as Run loop and all other life time operations
     * 
     */
    class Application
    {
    public:
        /**
         * @brief Construct the Singleton of Application and
         * starts the calls the Init function
         * 
         * @param props Windows Properties defining the title
         * as well as width and height
         */
        Application(const WindowProps &props);
        virtual ~Application();

        /**
         * @brief Initializes the systems that are needed for 
         * the application.
         * 
         * Creates the window with the properties defined in the constructor.
         * Initializes the Renderer.
         * Sets up the ImGui Layer as well when B_DEBUG is defined.
         * 
         * @param props Window Properties from the contrustor
         */
        virtual void Init(const WindowProps &props);

        /**
         * @brief Starts the run loop updating the layers and ImGui Layers
         * 
         */
        virtual void Run();

        // Function used for window event callbacks
        // Handles event dispatching
        /**
         * @brief Creates an Event Dispatcher and passes the event to layers
         * 
         * @param e The Event that will be dispatched
         * The event will toggle its Handled bool when a layer successfully uses it
         */
        void OnEvent(Event &e);

        /**
         * @brief Push a new layer onto the front of the stack.
         * Note: The LayerStack is updated in the reverse order
         * 
         * @param layer New Layer to add to the stack
         */
        void InsertLayer(Layer *layer);
        /**
         * @brief Pushing a new layer onto the back of the stack
         * - We mainly use this for Overlay/UI layers since we want those
         * layers to receive events for to block clicks and such from reaching
         * other layers
         * Note: The LayerStack is updated in the reverse order
         * 
         * @param layer New Overlay Layer to add to the stack
         */
        void InsertOverlay(Layer *layer);

        int LayerStackCount() const { return m_LayerStack.LayerCount(); }

        inline static bool Valid() { return s_Instance == nullptr; }
        /**
         * @brief Gets a reference to the singleton instance
         * 
         * @return Application& The Instance as a reference
         */
        inline static Application &Get() { return *s_Instance; }
        /**
         * @brief Get a reference to the Window
         * 
         * @return Window& The Window Instance as a reference
         */
        inline Window &GetWindow() { return *m_Window; }

        /**
         * @brief Sets the state of the Application to ShuttingDown.
         * Doing this will cause the Run loop to exit and start the
         * closing process
         * 
         */
        void Close();

#if defined(B_DEBUG)
        /**
         * @brief Get the ImGui layer that we use for debugging
         * 
         * @return ImGuiLayer* Debugging ImGui Layer
         */
        ImGuiLayer *GetImGuiLayer() { return m_ImGuiLayer; }
#endif

        /**
         * @brief Get the current Application State
         * 
         * @return ApplicationState
         */
        inline ApplicationState GetApplicationState() { return m_ApplicationState; }

    private:
        /**
         * @brief Function pointer for WindowCloseEvent
         * 
         * @param e Event
         * @return false Always
         */
        bool OnWindowClose(WindowCloseEvent &e);
        /**
         * @brief Function pointer for WindowResizeEvent
         * 
         * @param e Event
         * @return false Always
         */
        bool OnWindowResize(WindowResizeEvent &e);

    protected:
        /**
         * @brief Current State of the Application
         * 
         */
        ApplicationState m_ApplicationState = ApplicationState::Invalid;
        /**
         * @brief LayerStack containing all layers added to this application
         * 
         */
        LayerStack m_LayerStack;

    private:
        /**
         * @brief Scope for this Application's Window
         * 
         */
        Scope<Window> m_Window;

#if defined(B_DEBUG)
        /**
         * @brief Debugging ImGui layer
         * 
         */
        ImGuiLayer *m_ImGuiLayer;
#endif

        /**
         * @brief Delta Time of the application
         * 
         */
        float m_LastFrameTime = 0.0f;

    protected:
        /**
         * @brief Singleton Instance
         * 
         */
        static Application *s_Instance;
    };

    /**
     * @brief Function declaration for starting Bell
     * This should be defined within the Main File of the client.
     * 
     * @return Application* New Application pointer
     */
    Application *CreateApplication();
} // namespace Bell

#endif // !_APPLICATION_H