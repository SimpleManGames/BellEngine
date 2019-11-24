#include "bpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

namespace Bell
{
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        B_PROFILE_FUNCTION();

        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Shutdown()
    {
        B_PROFILE_FUNCTION();
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        B_PROFILE_FUNCTION();

        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4 transform)
    {
        B_PROFILE_FUNCTION();

        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}