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
        // Render Scene
        Camera *mainCamera = nullptr;
        glm::mat4 *mainCameraTransform = nullptr;
        {
            auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto entity : group)
            {
                auto &[camera, transform] = group.get<CameraComponent, TransformComponent>(entity);

                if (camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    mainCameraTransform = &transform.Transform;
                    break;
                }
            }
        }

        if (!mainCamera)
        {
            B_CORE_WARN("Main Camera in Scene does not exist. Make sure you set at least one camera to Primary!");
            return;
        }

        Renderer2D::BeginScene(mainCamera->GetProjectionMatrix(), *mainCameraTransform);

        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }

        Renderer2D::EndScene();
    }

    Entity Scene::CreateEntity(const std::string &tag, const glm::mat4 &transform)
    {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>(transform);
        entity.AddComponent<TagComponent>(tag);

        return entity;
    }

} // namespace Bell