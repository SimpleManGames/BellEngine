#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H

#include "Bell/Base/Core.h"

namespace Bell
{
    struct FrameBufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        virtual const FrameBufferSpecification& GetSpecification() const = 0;

        static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
    };
}

#endif // _FRAMEBUFFER_H