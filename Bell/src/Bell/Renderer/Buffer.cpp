#include "bpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Bell
{
    Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(size);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI")
            return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI")
            return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef< OpenGLIndexBuffer>(indices, size);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI")
            return nullptr;

    }
}