#include "bpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Bell
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        B_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        B_CORE_ASSERT(status, "Failed to initialize Glad");

        B_CORE_INFO("OpenGL Info:");
        B_CORE_INFO("  Vender: {0}", glGetString(GL_VENDOR));
        B_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        B_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}