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
        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
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

        if (entity.HasComponent<CameraComponent>())
        {
            if (ImGui::TreeNodeEx((void *)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera Component"))
            {
                auto &cameraComponent = entity.GetComponent<CameraComponent>();
                auto &camera = cameraComponent.Camera;

                const char *projectionTypeString[] = {"Perspective", "Orthographic"};
                const char *currentProjectionTypeString = projectionTypeString[(int)camera.GetProjectionType()];
                if (ImGui::BeginCombo("Project Method", currentProjectionTypeString))
                {
                    for (int i = 0; i < 2; i++)
                    {
                        bool isSelected = currentProjectionTypeString == projectionTypeString[i];
                        if (ImGui::Selectable(projectionTypeString[i], isSelected))
                        {
                            currentProjectionTypeString = projectionTypeString[i];
                            camera.SetProjectionType((SceneCamera::ProjectionType)i);
                        }

                        if (isSelected)
                        {
                            ImGui::SetItemDefaultFocus();
                        }
                    }
                    ImGui::EndCombo(); // Project Method
                }

                if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
                {
                    float verticalFov = glm::degrees(camera.GetPerspectiveVerticalFOV());
                    if (ImGui::DragFloat("Size", &verticalFov), 0.5f)
                    {
                        camera.SetPerspectiveVerticalFOV(glm::radians(verticalFov));
                    }
                    float nearClip = camera.GetPerspectiveNearClip();
                    if(ImGui::DragFloat("Near Clip", &nearClip), 0.5f)
                    {
                        camera.SetPerspectiveNearClip(nearClip);
                    }
                    float farClip = camera.GetPerspectiveFarClip();
                    if(ImGui::DragFloat("Far Clip", &farClip), 0.5f)
                    {
                        camera.SetPerspectiveFarClip(farClip);
                    }
                }

                if (cameraComponent.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
                {
                    float orthoSize = camera.GetOrthographicSize();
                    if (ImGui::DragFloat("Size", &orthoSize), 0.5f)
                    {
                        camera.SetOrthographicSize(orthoSize);
                    }
                    float nearClip = camera.GetOrthographicNearClip();
                    if(ImGui::DragFloat("Near Clip", &nearClip), 0.5f)
                    {
                        camera.SetOrthographicNearClip(nearClip);
                    }
                    float farClip = camera.GetOrthographicFarClip();
                    if(ImGui::DragFloat("Far Clip", &farClip), 0.5f)
                    {
                        camera.SetOrthographicFarClip(farClip);
                    }
                }

                ImGui::Checkbox("Primary", &cameraComponent.Primary);
                ImGui::Checkbox("Fixed Aspect", &cameraComponent.FixedAspectRatio);

                ImGui::TreePop();
            }
        }
    }

} // namespace Bell::Editor