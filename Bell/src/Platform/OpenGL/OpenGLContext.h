// OpenGL's version of the context abstraction 
// -------------------------------------------

#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "Bell/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Bell
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif // !OPENGLCONTEXT_H
