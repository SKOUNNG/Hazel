#include "hzpch.h"

#include "Application.h"
#include "Input.h"

#include "Hazel/Renderer/Renderer.h"

//#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

namespace Hazel
{

	Application* Application::s_Instance = nullptr;
	Application::Application()
		:m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		HZ_CORE_ASSERT(!s_Instance, "Application 总是存在！");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		//glfwSwapInterval(1);//设置垂直同步
		m_ImGuiLayer = new ImGuiLayer();

		PushOverlay(m_ImGuiLayer);
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.1f,0.1f,1.0f,
			0.5f,-0.5f,0.0f,0.1f,0.1f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.1f,0.8f,0.1f,1.0f
		};
		//Vertex Buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3,"a_Position"},
			{ShaderDataType::Float4,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0,1,2 };

		//Index Buffer
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f,-0.75f,0.0f,
			0.75f,-0.75f,0.0f,
			0.75f,0.75f,0.0f,
			-0.75f,0.75f,0.0f
		};

		std::shared_ptr<VertexBuffer> SquareVB;
		SquareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		BufferLayout squareLayout = {
			{ShaderDataType::Float3,"a_Position"},
		};
		SquareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(SquareVB);
		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };

		//Index Buffer
		std::shared_ptr<IndexBuffer> SquareIB;
		SquareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		//Shader
		std::string vertexSrc = R"(
		#version 460 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		uniform mat4 u_ViewProjection;
		out vec3 v_Position;
		out vec4 v_Color;
		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection*vec4(a_Position,1.0);
		}
		)";
		std::string fragmentSrc = R"(
		#version 460 core
		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		in vec4 v_Color;
		void main()
		{
			color = vec4(v_Position*0.5+0.5,1.0);
			color = v_Color;
		}
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		//Shader
		std::string vertexSrc2 = R"(
		#version 460 core
		layout(location = 0) in vec3 a_Position;
		uniform mat4 u_ViewProjection;
		out vec3 v_Position;
		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection*vec4(a_Position,1.0);
		}
		)";
		std::string fragmentSrc2 = R"(
		#version 460 core
		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		void main()
		{
			color = vec4(v_Position*0.5+0.5,1.0);
		}
		)";
		m_Shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
			RenderCommand::Clear();

			m_Camera.SetRotation(45.0f);

			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_Shader2, m_SquareVA);
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();



			//m_Shader2->Bind();
			//m_SquareVA->Bind();


			//m_Shader->Bind();
			//m_VertexArray->Bind();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			//auto [x, y] = Input::GetMousePosition();//鼠标位置事件
			//HZ_CORE_TRACE("{0}, {1}", x, y);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//HZ_CORE_TRACE(e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	Application::~Application()
	{

	}
}