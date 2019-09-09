#ifndef _RENDERER_H

#include "RenderCommand.h"

namespace Bell
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };

}

#endif // !_RENDERER_H
