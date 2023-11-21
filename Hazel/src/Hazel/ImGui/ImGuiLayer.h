#pragma once

#include "Hazel/Layer.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
/*
* ImGui�¼���Ӧ
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
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);//������
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);//�ͷ����
		bool OnMouseMovedEvent(MouseMovedEvent& e);//�ƶ����
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);//����������
		bool OnKeyPressedEvent(KeyPressedEvent& e);//����
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);//�ͷŰ���
		bool OnKeyTypedEvent(KeyTypedEvent& e);//�����ַ�����
		bool OnWindowResizeEvent(WindowResizeEvent& e);//���ڴ�С

	private:
		float m_Time = 0.0f;
	};
}