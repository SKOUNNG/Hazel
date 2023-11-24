#include <iostream>

#include <Hazel.h>

class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{

	}
	//轮询事件
	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update");//界面刷新
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
		{
			HZ_INFO("TAB按键被按下");
		}
	}
	//按键事件
	void OnEvent(Hazel::Event& event) override
	{
		//HZ_INFO("{0}", event);//打印事件操作
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			{
				HZ_TRACE("TAB, {0}", e.GetKeyCode());
			}
			else
			{
				HZ_TRACE("{0}, {1}", (char)e.GetKeyCode(), e.GetKeyCode());
			}
		}
		else if (event.GetEventType() == Hazel::EventType::MouseButtonPressed)
		{
			Hazel::MouseButtonEvent& e = (Hazel::MouseButtonEvent&)event;
			switch (e.GetMouseButton())
			{
			case 0:
				HZ_WARN("鼠标左键按下");
				break;
			case 1:
				HZ_WARN("鼠标右键按下");
				break;
			}
		}
	}
};

class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}


