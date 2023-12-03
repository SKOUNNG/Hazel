#include <hzpch.h>

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(m_WindowHandle, "WindowHandle 为空！")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Glad 未初始化！");
		HZ_CORE_INFO("OpenGL 信息:");
		HZ_CORE_INFO("    Vendor:\t\t{0}", (char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("    Renderer:\t\t{0}", (char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("    Version:\t\t{0}", (char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		//HZ_ERROR("Update");
		glfwSwapBuffers(m_WindowHandle);
	}
}
