#include "bpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bell
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}