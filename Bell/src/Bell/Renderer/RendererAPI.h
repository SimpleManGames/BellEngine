#ifndef _RENDERER_API_H
#define _RENDERER_API_H

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Bell
{
    class RendererAPI
    {
        // Types
    public:
        enum class API { None = 0, OpenGL = 1 };

        // Public methods
    public:
        virtual void Init() = 0;
        virtual void SetClearColor(const glm::vec4 color) = 0;
        virtual void Clear() = 0;
        
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}

#endif // !_RENDERER_API_H