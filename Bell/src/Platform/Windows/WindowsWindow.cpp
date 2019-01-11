#include "bpch.h"
#include "WindowsWindow.h"

#include "Bell/Events/ApplicationEvent.h"
#include "Bell/Events/MouseEvent.h"
#include "Bell/Events/KeyEvent.h"

#include <glad/glad.h>

namespace Bell 
{
    static bool s_GLFWInitialized = false;

    // Given to GLFW for error out
    static void GLFWErrorCallback(int error, const char* desr)
    {
        B_CORE_ERROR("GLFW Error ({0}): {1}", error, desr);
    }

    // Creates a new Window OS window using the defined properties
    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    // Initializes window with the defined properties 
    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        Init(props);
    }

    // Shuts down the windows
    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    // Initializes GLFW and creates GLFW window using the properties given
    void WindowsWindow::Init(const WindowProps& props)
    {
        // Set the wrapper's data
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        B_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        // Checks to see if we have GLFW already running
        if (!s_GLFWInitialized)
        {
            // Starts up GLFW
            int success = glfwInit();
            B_CORE_ASSERT(success, "Could not init GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        // Create the window
        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        // Puts in focus
        glfwMakeContextCurrent(m_Window);

        // Load Glad
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        B_CORE_ASSERT(status, "Failed to initialize Glad");

        // Grabs a pointer for us to use
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Set GLFW callbacks
        // Each one has a lambda function that 
        // Retrieves the WindowData reference
        // Sets any values that as associated with that event
        // Creates the specific event
        // Finally sets the WindowData reference EventCallback to use the new event

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallBack(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallBack(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallBack(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyPressedReleased event(key);
                    data.EventCallBack(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallBack(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallBack(event);
                    break;
                }

                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallBack(event);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallBack(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallBack(event);
        });
    }

    // Destroys the glfw window
    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    // Checks for glfw events and swap buffers
    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}