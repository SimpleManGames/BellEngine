// OpenGL's version of the context abstraction 
// -------------------------------------------

#ifndef _OPENGLCONTEXT_H
#define _OPENGLCONTEXT_H

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

#endif // !_OPENGLCONTEXT_H
