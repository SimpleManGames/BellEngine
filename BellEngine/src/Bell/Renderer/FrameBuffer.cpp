#include "bpch.h"
#include "Bell/Renderer/FrameBuffer.h"

#include "Bell/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Bell
{
    Ref<FrameBuffer> Bell::FrameBuffer::Create(const FrameBufferSpecification& spec)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr; break;
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLFrameBuffer>(spec);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI")
            return nullptr;
    }
}