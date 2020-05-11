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
            // TODO: Change this to textures loaded across all batches
            // Amount of used texture slots in the current batch
            uint32_t UsedTextureSlots;

            /// Frame Counter Data

            // Records multiple frames of render time
            std::array<float, 100> FrameRenderTime;
            uint32_t FrameCount = 0;
            float CurrentFrameBeginTime = 0.0f;
            float TotalFrameRenderTime = 0.0f;

            /// VRam Memory
            // Only working with NVIDIA right now
            uint32_t TotalMemoryInKB = 0;
            uint32_t CurrentAvailableMemoryInKB = 0;

            /// Helper Functions

            uint32_t GetTotalVertexCount() { return QuadCount * 4; }
            uint32_t GetTotalIndexCount() { return QuadCount * 6; }
        };

        static void StatsBeginFrame();
        static void StatsEndFrame();

        static Statistics const GetStats();
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
