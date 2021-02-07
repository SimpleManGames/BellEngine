#include "bpch.h"
#include "Bell/Scene/Scene.h"

#include "Bell/Scene/Entity.h"
#include "Bell/Scene/Components.h"
#include "Bell/Renderer/Renderer2D.h"

namespace Bell
{
    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    void Scene::OnUpdate(Timestep ts)
    {
        // Update scritps
        {
            m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto &nsc) {
                // TODO: Move this Instantiate code to the scene OnCreate
                if (!nsc.Instance)
                {
                    nsc.Instance = nsc.InstantiateScriptFunction();
                    nsc.Instance->m_Entity = {entity, this};
                    nsc.Instance->OnCreate();
                }

                nsc.Instance->OnUpdate(ts);
            });
        }

        // Render Scene
        Camera *mainCamera = nullptr;
        glm::mat4 mainCameraTransform;
        {
            auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto entity : group)
            {
                auto [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);

                if (camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    mainCameraTransform = transform.GetTransform();
                    break;
                }
            }
        }

        if (!mainCamera)
        {
            B_CORE_WARN("Main Camera in Scene does not exist. Make sure you set at least one camera to Primary!");
            return;
        }

        Renderer2D::BeginScene(mainCamera->GetProjectionMatrix(), mainCameraTransform);

        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
        }

        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;

        // Resize the non-fixed aspect ratio cameras within the scene
        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            if (auto &camera = view.get<CameraComponent>(entity);
                !camera.FixedAspectRatio)
            {
                camera.Camera.SetViewportSize(width, height);
            }
        }
    }

    Entity Scene::CreateEntity(const std::string &tag, const glm::vec3 &translation)
    {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>(translation);
        entity.AddComponent<TagComponent>(tag);

        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    template <typename T>
    void Scene::OnComponentAdded(Entity entity, T &component)
    {
        static_assert(false);
    }

    template <>
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent &component) {}

    template <>
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent &component)
    {
        component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    }

    template <>
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent &component) {}

    template <>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent &component) {}

    template <>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent &component) {}

} // namespace Bell