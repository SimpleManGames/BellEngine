#include "bpch.h"
#include "Bell/Renderer/GraphicsContext.h"

#include "Bell/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Bell
{
    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}