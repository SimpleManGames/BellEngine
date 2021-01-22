#ifndef _OPENGL_FRAMEBUFFER_H
#define _OPENGL_FRAMEBUFFER_H

#include "Bell/Renderer/FrameBuffer.h"

namespace Bell
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        void Bind() override;
        void Unbind() override;

        virtual uint32_t GetColorAttachmentRendererID() const override
        {
            return m_ColorAttachment;
        }

        virtual const FrameBufferSpecification& GetSpecification() const override
        {
            return m_Spec;
        }
    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthAttachment;
        FrameBufferSpecification m_Spec;
    };
}

#endif // _OPENGL_FRAMEBUFFER_H