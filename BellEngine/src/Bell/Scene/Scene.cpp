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
        auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
        for (auto entity : group)
        {
            auto &[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }
    }

    Entity Scene::CreateEntity(const std::string& tag, const glm::mat4& transform)
    {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>(transform);
        entity.AddComponent<TagComponent>(tag);

        return entity;
    }

} // namespace Bell