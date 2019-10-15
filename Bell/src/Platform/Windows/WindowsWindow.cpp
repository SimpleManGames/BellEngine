#include "bpch.h"
#include "WindowsWindow.h"

#include "Bell/Core/Events/ApplicationEvent.h"
#include "Bell/Core/Events/MouseEvent.h"
#include "Bell/Core/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

// Todo: move
#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((b) < (a)) ? (b) : (a))

namespace Bell
{
    static bool s_GLFWInitialized = false;

    // Given to GLFW for error out
    static void GLFWErrorCallback(int error, const char* desr)
    {
        B_CORE_ERROR("GLFW Error ({0}): {1}", error, desr);
    }

    // Creates a new Window OS window using the defined properties
    Ref<Window> Window::Create(const WindowProps& props)
    {
        return std::make_shared<WindowsWindow>(props);
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
        CenterWindow();

        m_Context = CreateScope<OpenGLContext>(m_Window);
        m_Context->Init();

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
                        KeyReleasedEvent event(key);
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

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyTypedEvent event(keycode);
                data.EventCallBack(event);
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

    void WindowsWindow::CenterWindow()
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(GetNativeWindow());
        GLFWmonitor* monitor = static_cast<GLFWmonitor*>(GetBestMonitor());
        if (!monitor)
            return;

        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        if (!mode)
            return;

        int monitorX, monitorY;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);

        glfwSetWindowPos(glfwWindow, 
            monitorX + (mode->width - GetWidth()) / 2,
            monitorY + (mode->height - GetHeight()) / 2);
    }

    void* WindowsWindow::GetBestMonitor()
    {
        GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(GetNativeWindow());
        if (!glfwWindow)
            return NULL;

        int monitorCount;
        GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);

        if (!monitors)
            return NULL;

        int windowX, windowY, windowWidth, windowHeight;
        glfwGetWindowSize(glfwWindow, &windowWidth, &windowHeight);
        glfwGetWindowPos(glfwWindow, &windowX, &windowY);

        GLFWmonitor* bestMonitor = NULL;
        int bestArea = 0;

        for (int i = 0; i < monitorCount; ++i)
        {
            GLFWmonitor* monitor = monitors[i];

            int monitorX, monitorY;
            glfwGetMonitorPos(monitor, &monitorX, &monitorY);

            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            if (!mode)
                continue;

            int areaMinX = MAX(windowX, windowX);
            int areaMinY = MAX(windowY, monitorY);

            int areaMaxX = MIN(windowX + windowWidth, monitorX + mode->width);
            int areaMaxY = MIN(windowY + windowHeight, monitorY + mode->height);

            int area = (areaMaxX - areaMinX) * (areaMaxY - areaMinY);

            if (area > bestArea)
            {
                bestArea = area;
                bestMonitor = monitor;
            }
        }

        return bestMonitor;
    }

    // Checks for glfw events and swap buffers
    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
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