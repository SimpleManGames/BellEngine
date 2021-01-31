#include "bpch.h"
#include "Bell/Renderer/Renderer2D.h"

#include "Bell/Renderer/RenderCommand.h"
#include "Bell/Renderer/Shader.h"
#include "Bell/Renderer/Data/VertexArray.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX 0x9048
#define GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX 0x9049

namespace Bell
{
    glm::vec2 Renderer2D::DefaultTexCoords[] = {{0.0, 0.0}, {1.0, 0.0}, {1.0, 1.0}, {0.0, 1.0}};

    // Describes the content of each Quad Vertex
    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float TilingFactor;
    };

    // Holds info about the Renderer2D
    struct Renderer2DData
    {
        // Max Quads Per Draw Call
        // This will be used to detect if a new batch is needed
        // TODO: Switch this from being const to getting it from
        //      the GPU
        static const uint32_t MaxQuadsPerDrawCall = 10000;
        // Max Vertices Per Draw Call
        // Stores the value of the max vertices to be quickly
        //      accessed later
        static const uint32_t MaxVerticesPerDrawCall = MaxQuadsPerDrawCall * 4;
        // Max Indices Per Draw Call
        // Stores the value of the max indices to be quickly
        //      accessed later
        static const uint32_t MaxIndicesPerDrawCall = MaxQuadsPerDrawCall * 6;
        // Max Texture Slots each batch can hold
        // Currently assuming we have 32 slots on our GPU
        // TODO: Switch this from static const to getting it from
        //      the GPU
        static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

        // TODO: Should be scopes once we control memory
        // VAO
        Ref<VertexArray> QuadVertexArray;
        // VBO
        Ref<VertexBuffer> QuadVertexBuffer;
        // Default shader we use when user doesn't specify one
        Ref<Shader> DefaultShader;

        // Stores a 1x1 white texture that we create
        //      in order to use it for color tinting
        Ref<Texture2D> WhiteTexture;

        // Keeps count of how many Indicies are in the current batch
        uint32_t QuadIndexCount = 0;
        // Stores the pointer to beginning of the Vertex Buffer
        QuadVertex *QuadVertexBufferBase = nullptr;
        // Stores the current location we are adding to in the
        //      Vertex Buffer
        QuadVertex *QuadVertexBufferPtr = nullptr;

        // The current Textures loaded for the batch
        // TODO: Switch to Asset Handle when implemented
        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        // Current spot in the TextureSlots array to load additional
        //      textures to the batch
        // Starts at one since we always want the white texture loaded
        uint32_t TextureSlotIndex = 1; // 0 = White Texture

        // Defines positions used for matrix math
        glm::vec4 QuadVertexPositions[4] =
            {
                {-0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, -0.5f, 0.0f, 1.0f},
                {0.5f, 0.5f, 0.0f, 1.0f},
                {-0.5f, 0.5f, 0.0f, 1.0f}};

        Renderer2D::Statistics Stats;
    };

    // Access point to the data
    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        B_PROFILE_FUNCTION();

        // Create and set up the VBO and VAO
        s_Data.QuadVertexArray = Bell::VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVerticesPerDrawCall * sizeof(QuadVertex));
        s_Data.QuadVertexBuffer->SetLayout({{ShaderDataType::Float3, "a_Position"},
                                            {ShaderDataType::Float4, "a_Color"},
                                            {ShaderDataType::Float2, "a_TexCoord"},
                                            {ShaderDataType::Float, "a_TexIndex"},
                                            {ShaderDataType::Float, "a_TilingFactor"}});
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVerticesPerDrawCall];

        uint32_t *quadIndices = new uint32_t[s_Data.MaxIndicesPerDrawCall];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxIndicesPerDrawCall; i += 6)
        {
            B_PROFILE_SCOPE("Setting Quad Indices");
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndicesPerDrawCall);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);

        delete[] quadIndices;

        // Create the white texture used for color tinting
        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        // Load samplers id
        int32_t samplers[s_Data.MaxTextureSlots];
        for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
        {
            B_PROFILE_SCOPE("Setting samplers ids");
            samplers[i] = i;
        }

        // Load the default shader
        s_Data.DefaultShader = Shader::Create("assets/shaders/Default.glsl");
        s_Data.DefaultShader->Bind();

        // Pass the sampler to the shader
        s_Data.DefaultShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

        // Set the zero index to the white texture
        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        // Set the vertex positions to the middle of the object
        s_Data.QuadVertexPositions[0] = {-0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[1] = {0.5f, -0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[2] = {0.5f, 0.5f, 0.0f, 1.0f};
        s_Data.QuadVertexPositions[3] = {-0.5f, 0.5f, 0.0f, 1.0f};

        GLint total_mem_kb = 0;
        glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);

        s_Data.Stats.TotalMemoryInKB = total_mem_kb;

        GLint cur_avail_mem_kb = 0;
        glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);

        s_Data.Stats.CurrentAvailableMemoryInKB = cur_avail_mem_kb;
    }

    void Renderer2D::Shutdown()
    {
        B_PROFILE_FUNCTION();

        delete[] s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene(const OrthographicCamera &camera)
    {
        B_PROFILE_FUNCTION();
        s_Data.DefaultShader->Bind();
        s_Data.DefaultShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        ResetBatchValues();
    }

    void Renderer2D::BeginScene(const Camera &camera, const glm::mat4 &transform)
    {
        B_PROFILE_FUNCTION();

        glm::mat4 viewProj = camera.GetProjectionMatrix() * glm::inverse(transform);

        s_Data.DefaultShader->Bind();
        s_Data.DefaultShader->SetMat4("u_ViewProjection", viewProj);

        ResetBatchValues();
    }

    void Renderer2D::EndScene()
    {
        B_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t *)s_Data.QuadVertexBufferPtr - (uint8_t *)s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        // Draw to the screen
        Flush();
    }

    void Bell::Renderer2D::FlushAndReset()
    {
        EndScene();
        ResetBatchValues();
    }

    void Bell::Renderer2D::ResetBatchValues()
    {
        B_PROFILE_FUNCTION();
        // Reset batch counts
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

        // Set to 1 in order not to over right the white texture
        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::Flush()
    {
        B_PROFILE_FUNCTION();

        // Don't draw if we don't have anything indexed
        if (s_Data.QuadIndexCount == 0)
        {
            return;
        }

        // Bind the textures we loaded for the batch
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            B_PROFILE_SCOPE("Binding Textures");
            s_Data.TextureSlots[i]->Bind(i);
        }

        // Draw
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

        // TODO: Add #if
        s_Data.Stats.DrawCalls++;
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationInRadian, const glm::vec4 &color)
    {
        DrawQuad(position, size, rotationInRadian, s_Data.WhiteTexture, color, 1.0f);
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationInRadian, const Ref<SubTexture2D> &subTexture, const glm::vec4 &colorTint, float textureScale)
    {
        DrawQuad(position, size, rotationInRadian, subTexture->GetTexture(), colorTint, textureScale, subTexture->GetTexCoords());
    }

    void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, float rotationInRadian, const Ref<Texture2D> &texture, const glm::vec4 &color, float tilingFactor, const glm::vec2 *texCoords)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotationInRadian, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
        DrawQuad(transform, texture, color, tilingFactor, texCoords);
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const glm::vec4 &color)
    {
        DrawQuad(transform, s_Data.WhiteTexture, color, 1.0f, Renderer2D::DefaultTexCoords);
    }

    void Renderer2D::DrawQuad(const glm::mat4 &transform, const Ref<Texture2D> &texture, const glm::vec4 &color, float tilingFactor, const glm::vec2 *texCoords)
    {
        B_PROFILE_FUNCTION();

        // If our index count is over our max per batch start a new batch
        if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndicesPerDrawCall)
        {
            B_CORE_INFO("Went over MaxIndicesPerDrawCall; Starting new batch");
            FlushAndReset();
        }

        constexpr uint32_t quadVertexCount = 4;

        int i = (true) ? 0 : 1;

        float textureIndex = -1.0f;

        // Only go up to the currently asigned texture slot to avoid iterating
        // Through all empty slots
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
        {
            B_PROFILE_SCOPE("Texture Lookup");
            if (texture == nullptr)
            {
                textureIndex = 1.0f;
                B_CORE_ERROR("Texture that was passed in is NULL!");
                break;
            }

            // Get the de-reference texture from a shared pointer
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                // Found the texture already loaded
                textureIndex = (float)i;
                break;
            }
        }

        // Texture not found
        if (textureIndex == -1.0f)
        {
            // Can't add anymore textures into a slot so start a new batch
            if (s_Data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
            {
                B_CORE_INFO("Went over MaxTextureSlots; Starting new batch!");
                FlushAndReset();
            }

            // Set the texture index to the next open slot
            textureIndex = (float)s_Data.TextureSlotIndex;
            // Set the texture slot at index to our new texture
            s_Data.TextureSlots[(uint32_t)textureIndex] = texture;
            // Increment were the next slot is
            s_Data.TextureSlotIndex++;

            // TODO: Add #if
            // Minus one since the TextureSlotIndex describes the next slot
            //      to be used
            s_Data.Stats.UsedTextureSlots = s_Data.TextureSlotIndex - 1;
        }

        for (int i = 0; i < quadVertexCount; i++)
        {
            B_PROFILE_SCOPE("Quad Vertex Setting");
            s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVertexBufferPtr->Color = color;
            s_Data.QuadVertexBufferPtr->TexCoord = texCoords[i];
            s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
            s_Data.QuadVertexBufferPtr->TilingFactor = tilingFactor;
            s_Data.QuadVertexBufferPtr++;
        }

        s_Data.QuadIndexCount += 6;

        // TODO: Add #if
        s_Data.Stats.QuadCount++;
    }

    void Renderer2D::StatsBeginFrame()
    {
        B_PROFILE_FUNCTION();
        s_Data.Stats.CurrentFrameBeginTime = (float)glfwGetTime();
    }

    void Renderer2D::StatsEndFrame()
    {
        B_PROFILE_FUNCTION();
        GLint total_mem_kb = 0;
        glGetIntegerv(GL_GPU_MEM_INFO_TOTAL_AVAILABLE_MEM_NVX, &total_mem_kb);

        s_Data.Stats.TotalMemoryInKB = total_mem_kb;

        GLint cur_avail_mem_kb = 0;
        glGetIntegerv(GL_GPU_MEM_INFO_CURRENT_AVAILABLE_MEM_NVX, &cur_avail_mem_kb);

        s_Data.Stats.CurrentAvailableMemoryInKB = cur_avail_mem_kb;

        s_Data.Stats.FrameRenderTime[s_Data.Stats.FrameCount] = (float)glfwGetTime() - s_Data.Stats.CurrentFrameBeginTime;
        s_Data.Stats.TotalFrameRenderTime += (s_Data.Stats.FrameRenderTime[s_Data.Stats.FrameCount] - s_Data.Stats.FrameRenderTime[(s_Data.Stats.FrameCount + (uint32_t)1) % s_Data.Stats.FrameRenderTime.size()]);
        if (++s_Data.Stats.FrameCount == s_Data.Stats.FrameRenderTime.size())
        {
            s_Data.Stats.FrameCount = 0;
        }
    }

    Renderer2D::Statistics const Bell::Renderer2D::GetStats()
    {
        B_PROFILE_FUNCTION();
        return s_Data.Stats;
    }

    void Bell::Renderer2D::ResetStats()
    {
        B_PROFILE_FUNCTION();
        auto frameRenderTime = s_Data.Stats.FrameRenderTime;
        auto frameCount = s_Data.Stats.FrameCount;
        auto totalFrameRenderTime = s_Data.Stats.TotalFrameRenderTime;
        memset(&s_Data.Stats, 0, sizeof(Renderer2D::Statistics));
        s_Data.Stats.FrameRenderTime = frameRenderTime;
        s_Data.Stats.FrameCount = frameCount;
        s_Data.Stats.TotalFrameRenderTime = totalFrameRenderTime;
    }
} // namespace Bell