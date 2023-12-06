#include "hzpch.h"
#include "VertexArray.h"

#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:HZ_CORE_ASSERT(false, "RendererAPI is None") return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}
		HZ_CORE_ASSERT(false, "Unknow RendererAPI");
		return nullptr;
	}
}