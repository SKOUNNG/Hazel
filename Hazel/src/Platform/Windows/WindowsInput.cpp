#include "hzpch.h"

#include "WindowsInput.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)//��ȡ����״̬
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, keycode);
		//HZ_ERROR("{0}, {1}", keycode,state);
		return state == GLFW_PRESS || state == GLFW_REPEAT;//�ж��Ƿ��°���
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)//��ȡ��갴��״̬
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		//HZ_ERROR("{0}", button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePositionImpl()//��ȡ���λ�ã�����ڳ������Ҳ���Ի�ȡ
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		//HZ_ERROR("{0}, {1}", x, y);
		return std::pair<float, float>(x, y);
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}