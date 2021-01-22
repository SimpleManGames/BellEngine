#include "bpch.h"
#include "Bell/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bell
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}