#include "bpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bell
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
    
    Scope<RendererAPI> RendererAPI::Create()
    {
        B_PROFILE_FUNCTION();
        switch (s_API)
        {
            case Bell::RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                    return nullptr;
            case Bell::RendererAPI::API::OpenGL:
                return CreateScope<OpenGLRendererAPI>();
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}