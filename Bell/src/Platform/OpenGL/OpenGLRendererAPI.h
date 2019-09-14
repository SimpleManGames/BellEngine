#ifndef _OPENGL_RENDERER_API_H
#define _OPENGL_RENDERER_API_H

#include "Bell/Renderer/RendererAPI.h"

namespace Bell
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4 color) override;
        virtual void Clear() override;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}

#endif // !_OPENGL_RENDERER_API_H
