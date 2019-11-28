#include "bpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Bell
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type)
        {
            case Bell::ShaderDataType::Float:  return GL_FLOAT;
            case Bell::ShaderDataType::Float2: return GL_FLOAT;
            case Bell::ShaderDataType::Float3: return GL_FLOAT;
            case Bell::ShaderDataType::Float4: return GL_FLOAT;
            case Bell::ShaderDataType::Mat3:   return GL_FLOAT;
            case Bell::ShaderDataType::Mat4:   return GL_FLOAT;
            case Bell::ShaderDataType::Int:    return GL_INT;
            case Bell::ShaderDataType::Int2:   return GL_INT;
            case Bell::ShaderDataType::Int3:   return GL_INT;
            case Bell::ShaderDataType::Int4:   return GL_INT;
            case Bell::ShaderDataType::Bool:   return GL_BOOL;
        }

        B_CORE_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        B_PROFILE_FUNCTION();
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        B_PROFILE_FUNCTION();
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        B_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        B_PROFILE_FUNCTION();
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
        B_PROFILE_FUNCTION();
        B_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.Offset);
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
        B_PROFILE_FUNCTION();
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

}