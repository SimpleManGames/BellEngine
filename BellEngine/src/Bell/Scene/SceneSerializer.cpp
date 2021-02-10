#include "bpch.h"
#include "Bell/Scene/SceneSerializer.h"

#include "Bell/Scene/Entity.h"
#include "Bell/Scene/Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Bell
{
    YAML::Emitter& operator <<(YAML::Emitter& out, const glm::vec3& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }
    
    YAML::Emitter& operator <<(YAML::Emitter& out, const glm::vec4& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }

    SceneSerializer::SceneSerializer(const Ref<Scene> scene)
        : m_Scene(scene)
    {
    }

    template <typename T, typename SerializationFunction>
    static void SerializeEntityComponent(const std::string &componentTypeString, YAML::Emitter &out, Entity entity, SerializationFunction serialize)
    {
        if (entity.HasComponent<T>())
        {
            out << YAML::Key << componentTypeString;
            out << YAML::BeginMap;

            serialize();

            out << YAML::EndMap;
        }
    }

    static void SerializeEntity(YAML::Emitter &out, Entity entity)
    {
        out << YAML::BeginMap;
        // TODO: When giving our entity class UID replace this Value
        out << YAML::Key << "Entity" << YAML::Value << "-1";

        SerializeEntityComponent<TagComponent>("TagComponent", out, entity, [&] {
            auto &tag = entity.GetComponent<TagComponent>().Tag;
            out << YAML::Key << "Tag" << YAML::Value << tag;
        });

        SerializeEntityComponent<TransformComponent>("TransformComponent", out, entity, [&] {
            auto &tc = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
            out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
            out << YAML::Key << "Scale" << YAML::Value << tc.Scale;
        });

        SerializeEntityComponent<CameraComponent>("CameraComponent", out, entity, [&] {
            auto &cc = entity.GetComponent<CameraComponent>();
            auto &camera = cc.Camera;
            out << YAML::Key << "Camera" << YAML::Value;
            out << YAML::BeginMap; // Camera
            out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
            out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();

            out << YAML::Key << "OrthograpicSize" << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << "OrthograpicNear" << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthograpicFar" << YAML::Value << camera.GetOrthographicFarClip();
            out << YAML::EndMap; // Camera

            out << YAML::Key << "Primary" << YAML::Value << cc.Primary;
            out << YAML::Key << "FixedAspectRatio" << YAML::Value << cc.FixedAspectRatio;
        });

        SerializeEntityComponent<SpriteRendererComponent>("SpriteRendererComponent", out, entity, [&] {
            auto &src = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << "Color" << YAML::Value << src.Color;
        });

        out << YAML::EndMap;
    }

    void SceneSerializer::Serialize(const std::string &filePath)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        // TODO: When adding a scene name to the Scene class replace the Value
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&](auto entityID) {
            Entity entity = {entityID, m_Scene.get()};
            if (!entity)
            {
                return;
            }

            SerializeEntity(out, entity);
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        // TODO: Create the folder if one doesn't exist already
        std::ofstream fout(filePath);
        fout << out.c_str();
    }

    void SceneSerializer::SerializeRuntime(const std::string &filePath)
    {
        B_CORE_ASSERT(false, "Not Implemented");
    }

    bool SceneSerializer::Deserialize(const std::string &filePath)
    {
        
    }

    bool SceneSerializer::DeserializeRuntime(const std::string &filePath)
    {
        B_CORE_ASSERT(false, "Not Implemented");
        return false;
    }
} // namespace Bell