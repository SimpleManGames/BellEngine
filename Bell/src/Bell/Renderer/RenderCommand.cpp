#include "bpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Bell
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}