#pragma once

#include "Hazel/Layer.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
/*
* ImGui事件相应
*/
namespace Hazel
{
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);//点击鼠标
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);//释放鼠标
		bool OnMouseMovedEvent(MouseMovedEvent& e);//移动鼠标
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);//滚动鼠标滚轮
		bool OnKeyPressedEvent(KeyPressedEvent& e);//按键
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);//释放按键
		bool OnKeyTypedEvent(KeyTypedEvent& e);//按键字符类型
		bool OnWindowResizeEvent(WindowResizeEvent& e);//窗口大小

	private:
		float m_Time = 0.0f;
	};
}