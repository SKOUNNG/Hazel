#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hazel
{
	static GLenum ShaderDataTypeToOenGLBaseType(ShaderDataType Type)
	{
		switch (Type)
		{
		case Hazel::ShaderDataType::None:		return GL_FLOAT;
		case Hazel::ShaderDataType::Float:		return GL_FLOAT;
		case Hazel::ShaderDataType::Float2:		return GL_FLOAT;
		case Hazel::ShaderDataType::Float3:		return GL_FLOAT;
		case Hazel::ShaderDataType::Float4:		return GL_FLOAT;
		case Hazel::ShaderDataType::Mat3:		return GL_FLOAT;
		case Hazel::ShaderDataType::Mat4:		return GL_FLOAT;
		case Hazel::ShaderDataType::Int:		return GL_INT;
		case Hazel::ShaderDataType::Int2:		return GL_INT;
		case Hazel::ShaderDataType::Int3:		return GL_INT;
		case Hazel::ShaderDataType::Int4:		return GL_INT;
		case Hazel::ShaderDataType::Bool:		return GL_BOOL;
		}
		HZ_CORE_ASSERT(false, "ShaderDataTypeToOenGLBaseType Error");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElement().size(), "vertex buffer has no layout");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		for (const auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			//第一个参数是索引，第二个是代表一个顶点的数字个数，第三个是顶点的类型，第四个是归一化，第五个是一个顶点占用多少字节，第六个是数据偏移量
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}
	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}