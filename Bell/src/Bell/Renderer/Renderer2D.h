#ifndef _RENDERER2D_H
#define _RENDERER2D_H

#include "Camera/OrthographicCamera.h"

#include "Texture.h"

namespace Bell
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        static void Flush();

        // Primitives
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& colorTint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float textureScale = 1.0f);
    };
}

#endif // !_RENDERER2D_H
