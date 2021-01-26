#ifndef _OPENGL_FRAMEBUFFER_H
#define _OPENGL_FRAMEBUFFER_H

#include "Bell/Renderer/FrameBuffer.h"

namespace Bell
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferSpecification &spec);
        virtual ~OpenGLFrameBuffer();

        void Invalidate();

        void Bind() override;
        void Unbind() override;

        void Resize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetColorAttachmentRendererID() const override
        {
            return m_ColorAttachment;
        }

        virtual const FrameBufferSpecification &GetSpecification() const override
        {
            return m_Spec;
        }

    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FrameBufferSpecification m_Spec;
    };
} // namespace Bell

#endif // _OPENGL_FRAMEBUFFER_H