#ifndef _OPENGL_SHADER_H
#define _OPENGL_SHADER_H

#include "Bell/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Bell
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t m_RendererID;
    };
}

#endif // !_OPENGL_SHADER_H
