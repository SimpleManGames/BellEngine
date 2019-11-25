#include "bpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Bell
{
    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(width, height);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLTexture2D>(path);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}