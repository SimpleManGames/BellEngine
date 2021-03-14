#include "bpch.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "stb_image.h"
#include <glad/glad.h>

namespace Bell {
    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_Width(width), m_Height(height)
    {
        B_PROFILE_FUNCTION();
        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;
        
        CreateTextureStorage();

        SetTextureParams();
    }

    OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
        : m_Path(path)
    {
        B_PROFILE_FUNCTION();
        // Output vars
        int width, height, channels;
        // Flip image for opengl
        stbi_set_flip_vertically_on_load(1);
        // Load image
        stbi_uc* data = nullptr;
        {
            B_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }
        // Validate
        B_CORE_ASSERT(data, "Failed to load image!");
        // Set our unsigned ints from the output vars int values
        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0;
        GLenum dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        B_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");
        
        CreateTextureStorage();

        SetTextureParams();

        // Load the actual pixal data from the pointer
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        // Free up data
        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        B_PROFILE_FUNCTION();
        glDeleteTextures(1, &m_RendererID);
    }
    
    void OpenGLTexture2D::SetData(void* data, uint32_t size)
    {
        B_PROFILE_FUNCTION();
#ifdef B_ENABLE_ASSERTS
        // Bytes per pixel
        uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
        B_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be set to entire texture!");
#endif
        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        B_PROFILE_FUNCTION();
        glBindTextureUnit(slot, m_RendererID);
    }

    void OpenGLTexture2D::CreateTextureStorage()
    {
        // Start creating and set a block of memory to load it to
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
    }

    void OpenGLTexture2D::SetTextureParams()
    {
        // Texture parameters definitions
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
}