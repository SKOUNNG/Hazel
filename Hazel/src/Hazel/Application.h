#pragma once

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow()
		{
			return *m_Window;
		}
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		LayerStack m_LayerStack;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

