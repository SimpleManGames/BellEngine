#include "Panels/SceneHierarchyPanel.h"

#include <imgui.h>
#include <imgui_internal.h>
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

        // Right click menu on blank space
        if (ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
            {
                m_Context->CreateEntity("Empty Entity");
            }

            ImGui::EndPopup();
        }

        ImGui::End(); // Scene Hierarchy

        ImGui::Begin("Properties");

        if (m_SeletectionContext)
        {
            DrawComponents(m_SeletectionContext);

            if (ImGui::Button("Add Component"))
            {
                ImGui::OpenPopup("AddComponent");
            }

            if (ImGui::BeginPopup("AddComponent"))
            {
                if (ImGui::MenuItem("Camera"))
                {
                    m_SeletectionContext.AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Sprite Renderer"))
                {
                    m_SeletectionContext.AddComponent<SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
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
            m_SeletectionContext = entity;

        // Deffer deletion later so that we don't throw ImGui errors
        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (opened)
            ImGui::TreePop();

        if (entityDeleted)
        {
            m_Context->DestroyEntity(entity);
            if (m_SeletectionContext == entity)
                m_SeletectionContext = {};
        }
    }

    static void DrawVec3Control(const std::string &label, glm::vec3 &values, float resetValue = 0.0f, float columnWidth = 100.0f)
    {
        // Each label must currently being displayed needs a different label or
        // they will control each other
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columnWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.9f, 0.2f, 0.25f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.8f, 0.1f, 0.15f, 1.0f});
        if (ImGui::Button("X", buttonSize))
        {
            values.x = resetValue;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.8f, 0.3f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.2f, 0.7f, 0.2f, 1.0f});
        if (ImGui::Button("Y", buttonSize))
        {
            values.y = resetValue;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.2f, 0.35f, 0.9f, 1.0f});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.1f, 0.25f, 0.8f, 1.0f});
        if (ImGui::Button("Z", buttonSize))
        {
            values.z = resetValue;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);
        ImGui::PopID();
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

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
            if (ImGui::TreeNodeEx((void *)typeid(TransformComponent).hash_code(), treeNodeFlags, "Transform"))
            {
                auto &transformComponent = entity.GetComponent<TransformComponent>();
                DrawVec3Control("Translation", transformComponent.Translation);
                // Use degrees for easier readablity
                glm::vec3 rotation = glm::degrees(transformComponent.Rotation);
                DrawVec3Control("Rotation", rotation);
                transformComponent.Rotation = glm::radians(rotation);
                DrawVec3Control("Scale", transformComponent.Scale, 1.0f);

                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<CameraComponent>())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});

            bool open = ImGui::TreeNodeEx((void *)typeid(CameraComponent).hash_code(), treeNodeFlags, "Camera");
            ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
            if (ImGui::Button("+", ImVec2{20, 20}))
            {
                ImGui::OpenPopup("ComponentSettings");
            }
            ImGui::PopStyleVar();

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                auto &cameraComponent = entity.GetComponent<CameraComponent>();
                auto &camera = cameraComponent.Camera;

                const char *projectionTypeString[] = {"Perspective", "Orthographic"};
                const char *currentProjectionTypeString = projectionTypeString[(int)camera.GetProjectionType()];
                if (ImGui::BeginCombo("Projection Method", currentProjectionTypeString))
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
                    if (ImGui::DragFloat("Near Clip", &nearClip), 0.5f)
                    {
                        camera.SetPerspectiveNearClip(nearClip);
                    }
                    float farClip = camera.GetPerspectiveFarClip();
                    if (ImGui::DragFloat("Far Clip", &farClip), 0.5f)
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
                    if (ImGui::DragFloat("Near Clip", &nearClip), 0.5f)
                    {
                        camera.SetOrthographicNearClip(nearClip);
                    }
                    float farClip = camera.GetOrthographicFarClip();
                    if (ImGui::DragFloat("Far Clip", &farClip), 0.5f)
                    {
                        camera.SetOrthographicFarClip(farClip);
                    }
                }

                ImGui::Checkbox("Primary", &cameraComponent.Primary);
                ImGui::Checkbox("Fixed Aspect", &cameraComponent.FixedAspectRatio);

                ImGui::TreePop();
            }

            if (removeComponent)
                entity.RemoveComponent<CameraComponent>();
        }

        if (entity.HasComponent<SpriteRendererComponent>())
        {
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{4, 4});

            bool open = ImGui::TreeNodeEx((void *)typeid(SpriteRendererComponent).hash_code(), treeNodeFlags, "Sprite");
            ImGui::SameLine(ImGui::GetWindowWidth() - 25.0f);
            if (ImGui::Button("+", ImVec2{20, 20}))
            {
                ImGui::OpenPopup("ComponentSettings");
            }
            ImGui::PopStyleVar();

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                auto &spriteComponent = entity.GetComponent<SpriteRendererComponent>();
                auto &color = spriteComponent.Color;

                ImGui::ColorEdit4("Tint", glm::value_ptr(color));

                ImGui::TreePop();
            }

            if (removeComponent)
                entity.RemoveComponent<SpriteRendererComponent>();
        }
    }

} // namespace Bell::Editor