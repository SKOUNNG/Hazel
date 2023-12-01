#include <hzpch.h>

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(m_WindowHandle,"WindowHandle Ϊ�գ�")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Glad δ��ʼ����");
	}
	void OpenGLContext::SwapBuffers()
	{
		//HZ_ERROR("Update");
		glfwSwapBuffers(m_WindowHandle);
	}
}
