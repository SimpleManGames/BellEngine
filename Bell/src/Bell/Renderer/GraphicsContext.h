// Graphics Context Abstraction
// Each supported Rendering Library will have it's own implementation
// ------------------------------------------------------------------

#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace Bell
{
    class GraphicsContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif // !GRAPHICSCONTEXT_H