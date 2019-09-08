#include "bpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Bell
{
    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::OpenGL:
                return new OpenGLVertexArray();
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI")
            return nullptr;
    }
}