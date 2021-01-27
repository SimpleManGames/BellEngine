// Graphics Context Abstraction
// Each supported Rendering Library will have it's own implementation
// ------------------------------------------------------------------

#ifndef _GRAPHICSCONTEXT_H
#define _GRAPHICSCONTEXT_H

namespace Bell
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<GraphicsContext> Create(void *window);
    };
} // namespace Bell

#endif // !_GRAPHICSCONTEXT_H