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
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& colorTint = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), float textureScale = 1.0f);

        // Render stats for debugging
        struct Statistics
        {
            // Amount of draw calls per reset
            uint32_t DrawCalls = 0;
            // Amount of quads per reset
            uint32_t QuadCount = 0;

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static Statistics GetStats();
        static void ResetStats();

    private:
        /// Ends current scene and starts a new batch without needed
        ///     to set camera and bind shaders
        static void FlushAndReset();

        /// Resets current batch in order to flush
        static void ResetBatchValues();
    };
}

#endif // !_RENDERER2D_H
