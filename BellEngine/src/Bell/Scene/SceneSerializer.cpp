#include "bpch.h"
#include "Bell/Scene/SceneSerializer.h"

#include "Bell/Scene/Entity.h"
#include "Bell/Scene/Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

/// Create our own encode/decode instructions for complex types

namespace YAML
{
    template <>
    struct convert<glm::vec3>
    {
        static Node encode(const glm::vec3 &rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            return node;
        }

        static bool decode(const Node &node, glm::vec3 &rhs)
        {
            if (!node.IsSequence() || node.size() != 3)
            {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template <>
    struct convert<glm::vec4>
    {
        static Node encode(const glm::vec4 &rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            return node;
        }

        static bool decode(const Node &node, glm::vec4 &rhs)
        {
            if (!node.IsSequence() || node.size() != 4)
            {
                return false;
            }

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
} // namespace YAML

namespace Bell
{
    // Bit shift operators for glm types

    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }

    namespace YAMLKeys
    {
        const std::string Scene = "Scene";
        const std::string Entity = "Entity";
        const std::string Entities = "Entities";

        const std::string TagComponent = "TagComponent";
        const std::string Tag = "Tag";

        const std::string TransformComponent = "TransformComponent";
        const std::string Translation = "Translation";
        const std::string Rotation = "Rotation";
        const std::string Scale = "Scale";

        const std::string CameraComponent = "CameraComponent";
        const std::string Camera = "Camera";

        const std::string ProjectionType = "ProjectionType";
        const std::string PerspectiveFOV = "PerspectiveFOV";
        const std::string PerspectiveNear = "PerspectiveNear";
        const std::string PerspectiveFar = "PerspectiveFar";

        const std::string OrthographicSize = "OrthographicSize";
        const std::string OrthographicNear = "OrthographicNear";
        const std::string OrthographicFar = "OrthographicFar";

        const std::string Primary = "Primary";
        const std::string FixedAspectRatio = "FixedAspectRatio";
        
        const std::string SpriteRendererComponent = "SpriteRendererComponent";
        const std::string Color = "Color";
    } // namespace YAMLKeys

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
        out << YAML::Key << YAMLKeys::Entity << YAML::Value << "0";

        SerializeEntityComponent<TagComponent>(YAMLKeys::TagComponent, out, entity, [&] {
            auto &tag = entity.GetComponent<TagComponent>().Tag;
            out << YAML::Key << YAMLKeys::Tag << YAML::Value << tag;
        });

        SerializeEntityComponent<TransformComponent>(YAMLKeys::TransformComponent, out, entity, [&] {
            auto &tc = entity.GetComponent<TransformComponent>();
            out << YAML::Key << YAMLKeys::Translation << YAML::Value << tc.Translation;
            out << YAML::Key << YAMLKeys::Rotation << YAML::Value << tc.Rotation;
            out << YAML::Key << YAMLKeys::Scale << YAML::Value << tc.Scale;
        });

        SerializeEntityComponent<CameraComponent>(YAMLKeys::CameraComponent, out, entity, [&] {
            auto &cc = entity.GetComponent<CameraComponent>();
            auto &camera = cc.Camera;
            out << YAML::Key << YAMLKeys::Camera << YAML::Value;
            out << YAML::BeginMap; // Camera
            out << YAML::Key << YAMLKeys::ProjectionType << YAML::Value << (int)camera.GetProjectionType();
            out << YAML::Key << YAMLKeys::PerspectiveFOV << YAML::Value << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << YAMLKeys::PerspectiveNear << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << YAMLKeys::PerspectiveFar << YAML::Value << camera.GetPerspectiveFarClip();

            out << YAML::Key << YAMLKeys::OrthographicSize << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << YAMLKeys::OrthographicNear << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << YAMLKeys::OrthographicFar << YAML::Value << camera.GetOrthographicFarClip();
            out << YAML::EndMap; // Camera

            out << YAML::Key << YAMLKeys::Primary << YAML::Value << cc.Primary;
            out << YAML::Key << YAMLKeys::FixedAspectRatio << YAML::Value << cc.FixedAspectRatio;
        });

        SerializeEntityComponent<SpriteRendererComponent>(YAMLKeys::SpriteRendererComponent, out, entity, [&] {
            auto &src = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << YAMLKeys::Color << YAML::Value << src.Color;
        });

        out << YAML::EndMap;
    }

    void SceneSerializer::Serialize(const std::string &filePath)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        // TODO: When adding a scene name to the Scene class replace the Value
        out << YAML::Key << YAMLKeys::Scene << YAML::Value << "Untitled";
        out << YAML::Key << YAMLKeys::Entities << YAML::Value << YAML::BeginSeq;
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
        std::ifstream stream(filePath);
        std::stringstream strStream;
        strStream << stream.rdbuf();

        YAML::Node data = YAML::Load(strStream.str());
        if (!data[YAMLKeys::Scene])
        {
            B_CORE_WARN("File at {0} was attempted to be Deserialized but could not find Scene YAML section", filePath);
            return false;
        }

        std::string sceneName = data["Scene"].as<std::string>();
        B_CORE_TRACE("Deserializing scene '{0}'", sceneName);

        auto entities = data[YAMLKeys::Entities];
        if (entities)
        {
            for (auto entity : entities)
            {
                // TODO: Assign a proper UUID to the entity
                uint64_t uuid = entity[YAMLKeys::Entity].as<uint64_t>();

                std::string name;
                if (auto tc = entity[YAMLKeys::TagComponent])
                {
                    name = tc[YAMLKeys::Tag].as<std::string>();
                }

                B_CORE_TRACE("Deserialized Entity with ID = {0}, Name = {1}", uuid, name);
                // TODO: Create Entity with UUID
                Entity deserializedEntity = m_Scene->CreateEntity(name);

                if (auto tc = entity[YAMLKeys::TransformComponent])
                {
                    auto &component = deserializedEntity.GetComponent<TransformComponent>();
                    component.Translation = tc[YAMLKeys::Translation].as<glm::vec3>();
                    component.Rotation = tc[YAMLKeys::Rotation].as<glm::vec3>();
                    component.Scale = tc[YAMLKeys::Scale].as<glm::vec3>();
                }

                if (auto cc = entity[YAMLKeys::CameraComponent])
                {
                    auto &component = deserializedEntity.AddComponent<CameraComponent>();

                    auto &cameraProps = cc[YAMLKeys::Camera];
                    component.Camera.SetProjectionType((SceneCamera::ProjectionType)cameraProps[YAMLKeys::ProjectionType].as<int>());

                    component.Camera.SetPerspectiveVerticalFOV(cameraProps[YAMLKeys::PerspectiveFOV].as<float>());
                    component.Camera.SetPerspectiveNearClip(cameraProps[YAMLKeys::PerspectiveNear].as<float>());
                    component.Camera.SetPerspectiveFarClip(cameraProps[YAMLKeys::PerspectiveFar].as<float>());

                    component.Camera.SetOrthographicSize(cameraProps[YAMLKeys::OrthographicSize].as<float>());
                    component.Camera.SetOrthographicNearClip(cameraProps[YAMLKeys::OrthographicNear].as<float>());
                    component.Camera.SetOrthographicFarClip(cameraProps[YAMLKeys::OrthographicFar].as<float>());

                    component.Primary = cc[YAMLKeys::Primary].as<bool>();
                    component.FixedAspectRatio = cc[YAMLKeys::FixedAspectRatio].as<bool>();
                }

                if (auto src = entity[YAMLKeys::SpriteRendererComponent])
                {
                    auto &component = deserializedEntity.AddComponent<SpriteRendererComponent>();
                    component.Color = src[YAMLKeys::Color].as<glm::vec4>();
                }
            }
        }

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string &filePath)
    {
        B_CORE_ASSERT(false, "Not Implemented");
        return false;
    }
} // namespace Bell