#ifndef _RENDERER2D_H
#define _RENDERER2D_H

#include "Camera/OrthographicCamera.h"

namespace Bell
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        //static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
        // TODO: DrawQuad with rotation
    };
}

#endif // !_RENDERER2D_H
