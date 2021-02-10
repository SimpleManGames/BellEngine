#ifndef SCENESERIALIZER_H
#define SCENESERIALIZER_H

#include "Scene.h"

namespace Bell
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const Ref<Scene> scene);

        /**
         * @brief Serialize the scene which we have the context of to
         * a specific file location as a yaml format
         * 
         * @param filePath Destination of the saved asset
         */
        void Serialize(const std::string &filePath);
        /**
         * @brief Serialize the scene which we have the context of to
         * a specific file location as a binary format
         * 
         * @param filePath Location of the saved asset
         */
        void SerializeRuntime(const std::string &filePath);

        /**
         * @brief Deserialize a scene file at specified file path from a yaml format
         * 
         * @param filePath Destination of the saved asset
         * 
         * @return A Bool if the Deserialization is successful
         */
        bool Deserialize(const std::string &filePath);
        /**
         * @brief Deserialize a scene file at specified file path from a binary format
         * 
         * @param filePath Location of the saved asset
         * 
         * @return A Bool if the Deserialization is successful
         */
        bool DeserializeRuntime(const std::string &filePath);

    private:
        Ref<Scene> m_Scene;
    };
    
} // namespace Bell

#endif // SCENESERIALIZER_H