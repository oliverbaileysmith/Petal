#include "ptlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace ptl
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
