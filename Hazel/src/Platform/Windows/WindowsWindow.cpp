#include "hzpch.h"
#include "WindowsWindow.h"
#include "WindowsInput.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Hazel {

	static void GLFWErrorCallback(const int code, const char* message)
	{
		HZ_CORE_ERROR("GLFW Error ({0}) : {1}", code, message);
	}

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Cloud not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//设置GLFW回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)//设置窗口大小
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				HZ_ERROR("{0}, {1}", width, height);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)//窗口关闭
			{
				HZ_ERROR("程序关闭！");
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)//获取按键状态
			{//key是按键，scancode不同平台的按键码，action按键状态
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//HZ_ERROR("{0}, {1}, {2}, {3}", key, scancode, action, mods);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)//键盘输入获取
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//HZ_ERROR("{0}", keycode);//键盘码获取
				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)//鼠标按键事件获取
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)//action是鼠标按键状态
				{
				case GLFW_PRESS:
				{
					//按下
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					//释放
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)//鼠标滚轮
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			//获取鼠标位置，鼠标移除程序则无法获取
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				//HZ_WARN("{0}, {1}", xPos, yPos);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()//关闭函数
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()//刷新函数
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}