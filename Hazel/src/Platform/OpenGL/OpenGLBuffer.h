#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind();
		virtual void UnBind();
	private:
		uint32_t m_RendererID;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
		virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() { return m_Count; }
		virtual void Bind();
		virtual void UnBind();
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}