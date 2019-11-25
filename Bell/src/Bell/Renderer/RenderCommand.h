#ifndef _RENDER_COMANND_H
#define _RENDER_COMANND_H

#include "RendererAPI.h"

namespace Bell
{
    class RenderCommand
    {
    public:
        inline static void Init()
        {
            B_PROFILE_FUNCTION();
            s_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            B_PROFILE_FUNCTION();
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        inline static void SetClearColor(const glm::vec4 color)
        {
            B_PROFILE_FUNCTION();
            s_RendererAPI->SetClearColor(color);
        }
        inline static void Clear()
        {
            B_PROFILE_FUNCTION();
            s_RendererAPI->Clear();
        }
        inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            B_PROFILE_FUNCTION();
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}

#endif // !_RENDER_COMANND_H
