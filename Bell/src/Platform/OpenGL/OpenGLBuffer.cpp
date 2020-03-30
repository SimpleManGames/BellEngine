#include "bpch.h"
#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace Bell
{
#pragma region VertexBuffer

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        B_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        B_PROFILE_FUNCTION();
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        B_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        B_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        B_PROFILE_FUNCTION();
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

#pragma endregion

#pragma region IndexBuffer

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        : m_Count(count)
    {
        B_PROFILE_FUNCTION();
        glCreateBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        B_PROFILE_FUNCTION();
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        B_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        B_PROFILE_FUNCTION();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

#pragma endregion
}