#include "bpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bell
{
    Ref<VertexArray> VertexArray::Create()
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef< OpenGLVertexArray>();
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
}