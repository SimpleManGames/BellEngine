#include "bpch.h"
#include "Renderer2D.h"

#include "RenderCommand.h"
#include "VertexArray.h"
#include "Shader.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bell
{
    struct Renderer2DStorage
    {
        // TODO: Should be scopes once we control memory
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> DefaultShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage* s_StorageData;

    void Renderer2D::Init()
    {
        B_PROFILE_FUNCTION();

        s_StorageData = new Renderer2DStorage();

        s_StorageData->QuadVertexArray = Bell::VertexArray::Create();

        float squareVertices[5 * 4] = {
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        Ref<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
            });
        s_StorageData->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_StorageData->QuadVertexArray->SetIndexBuffer(squareIB);

        s_StorageData->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_StorageData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_StorageData->DefaultShader = Shader::Create("../assets/shaders/Default.glsl");
        s_StorageData->DefaultShader->Bind();
        s_StorageData->DefaultShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shutdown()
    {
        B_PROFILE_FUNCTION();
        delete s_StorageData;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        B_PROFILE_FUNCTION();
        s_StorageData->DefaultShader->Bind();
        s_StorageData->DefaultShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {
        B_PROFILE_FUNCTION();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y , 0 }, size, rotation, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
    {
        DrawQuad(position, size, rotation, s_StorageData->WhiteTexture, color, 1.0f);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale)
    {
        DrawQuad({ position.x, position.y , 0 }, size, rotation, texture, color, textureScale);
    }
    
    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& color, float textureScale)
    {
        B_PROFILE_FUNCTION();
        texture->Bind();
        s_StorageData->DefaultShader->SetFloat4("u_Color", color);
        s_StorageData->DefaultShader->SetFloat("u_TextureScale", textureScale);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
            * glm::rotate(glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f))
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        s_StorageData->DefaultShader->SetMat4("u_Transform", transform);

        s_StorageData->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_StorageData->QuadVertexArray);
    }
}