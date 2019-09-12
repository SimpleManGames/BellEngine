#ifndef _OPENGL_SHADER_H
#define _OPENGL_SHADER_H

#include "Bell/Renderer/Shader.h"
#include <glm/glm.hpp>

#define OpenGLShaderCast(x) std::dynamic_pointer_cast<Bell::OpenGLShader>(x)

namespace Bell
{

    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformInt(const std::string& name, int value);

        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        uint32_t m_RendererID;
    };
}

#endif // !_OPENGL_SHADER_H
