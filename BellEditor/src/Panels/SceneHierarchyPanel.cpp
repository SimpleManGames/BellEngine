#include "Panels/SceneHierarchyPanel.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Bell::Editor
{
    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene> &context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene> &context)
    {
        m_Context = context;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        m_Context->m_Registry.each([&](auto entityID) {
            Entity entity{entityID, m_Context.get()};
            DrawEntityNode(entity);
        });

        // Deselect if clicking in an empty space
        if(ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
        {
            m_SeletectionContext = {};
        }

        ImGui::End(); // Scene Hierarchy

        ImGui::Begin("Properties");

        if (m_SeletectionContext)
        {
            DrawComponents(m_SeletectionContext);
        }

        ImGui::End(); // Properties
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto &tag = entity.GetComponent<TagComponent>().Tag;

        // Only use the _Selected flag if this entity is the selected one
        ImGuiTreeNodeFlags flags = ((m_SeletectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        // Use the id from entt as the ptr value for the tree
        bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)entity, flags, tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SeletectionContext = entity;
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<TagComponent>())
        {
            auto &tag = entity.GetComponent<TagComponent>().Tag;

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx((void *)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform Component"))
            {
                auto &transform = entity.GetComponent<TransformComponent>().Transform;
                ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.5f);

                ImGui::TreePop();
            }
        }
    }

} // namespace Bell::Editor