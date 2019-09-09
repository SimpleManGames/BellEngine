#ifndef _RENDER_COMANND_H
#define _RENDER_COMANND_H

#include "RendererAPI.h"

namespace Bell
{
    class RenderCommand
    {
    public:
        inline static void SetClearColor(const glm::vec4 color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        inline static void Clear()
        {
            s_RendererAPI->Clear();
        }
        inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* s_RendererAPI;
    };
}

#endif // !_RENDER_COMANND_H
