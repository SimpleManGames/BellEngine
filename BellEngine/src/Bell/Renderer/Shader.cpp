#include "bpch.h"
#include "Bell/Renderer/Shader.h"

#include "Bell/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Bell
{
    Ref<Shader> Shader::Create(const std::string& filePath)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(filePath);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        B_PROFILE_FUNCTION();
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
                B_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        B_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
    
    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        B_PROFILE_FUNCTION();
        B_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        B_PROFILE_FUNCTION();
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
    {
        B_PROFILE_FUNCTION();
        auto shader = Shader::Create(filePath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
    {
        B_PROFILE_FUNCTION();
        auto shader = Shader::Create(filePath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string& name)
    {
        B_PROFILE_FUNCTION();
        B_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }
    bool ShaderLibrary::Exists(const std::string& name) const
    {
        B_PROFILE_FUNCTION();
        return m_Shaders.find(name) != m_Shaders.end();
    }
}