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
        B_PROFILE_FUNCTION();
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        B_CORE_ASSERT(status, "Failed to initialize Glad");

        B_CORE_INFO("OpenGL Info:");
        B_CORE_INFO("  Vender: {0}", glGetString(GL_VENDOR));
        B_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        B_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

#ifdef B_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        B_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Bell requires at least OpenGL version 4.5");
#endif
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}