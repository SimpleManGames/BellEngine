#ifndef _RENDERER_H
#define _RENDERER_H

#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Bell
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* s_SceneData;
    };

}

#endif // !_RENDERER_H
