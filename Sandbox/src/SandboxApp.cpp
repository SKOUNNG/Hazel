﻿#include <iostream>

#include <Hazel.h>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer :public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f),
		m_CameraMovedSpeed(1.0f),
		m_CameraRotation(0.0f),
		m_CameraRotationSpeed(100.0f),
		m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Hazel::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f,-0.5f,0.0f,0.8f,0.1f,0.1f,1.0f,
			0.5f,-0.5f,0.0f,0.1f,0.1f,0.8f,1.0f,
			0.0f,0.5f,0.0f,0.1f,0.8f,0.1f,1.0f
		};
		//Vertex Buffer
		Hazel::Ref<Hazel::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Hazel::VertexBuffer::Create(vertices, sizeof(vertices)));
		Hazel::BufferLayout layout = {
			{Hazel::ShaderDataType::Float3,"a_Position"},
			{Hazel::ShaderDataType::Float4,"a_Color"}
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		uint32_t indices[3] = { 0,1,2 };

		//Index Buffer
		Hazel::Ref<Hazel::IndexBuffer> indexBuffer;
		indexBuffer.reset(Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Hazel::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f,-0.5f,0.0f,
			0.5f,-0.5f,0.0f,
			0.5f,0.5f,0.0f,
			-0.5f,0.5f,0.0f
		};

		Hazel::Ref<Hazel::VertexBuffer> SquareVB;
		SquareVB.reset(Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Hazel::BufferLayout squareLayout = {
			{Hazel::ShaderDataType::Float3,"a_Position"},
		};
		SquareVB->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(SquareVB);
		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };

		//Index Buffer
		Hazel::Ref<Hazel::IndexBuffer> SquareIB;
		SquareIB.reset(Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(SquareIB);

		//Shader
		std::string vertexSrc = R"(
		#version 460 core
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;
		out vec3 v_Position;
		out vec4 v_Color;
		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjection*u_Transform*vec4(a_Position,1.0);
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
		m_Shader.reset(Hazel::Shader::Create(vertexSrc, fragmentSrc));
		//Shader
		std::string flatColorShaderVertexSrc = R"(
		#version 460 core
		layout(location = 0) in vec3 a_Position;
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;
		out vec3 v_Position;
		void main()
		{
			v_Position = a_Position;
			gl_Position = u_ViewProjection*u_Transform*vec4(a_Position,1.0);
		}
		)";
		std::string flatColorShaderFragmentSrc = R"(
		#version 460 core
		layout(location = 0) out vec4 color;
		in vec3 v_Position;
		uniform vec3 u_Color;
		void main()
		{
			color = vec4(u_Color,1.0);
		}
		)";
		m_FlatColorShader.reset(Hazel::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}
	//轮询事件
	void OnUpdate(Hazel::Timestep ts) override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMovedSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMovedSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMovedSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMovedSpeed * ts;
		}
		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		Hazel::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
		Hazel::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Hazel::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		//Hazel::MaterialRef material = new Hazel::Material(m_FlatColorShader);

		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}
		Hazel::Renderer::Submit(m_Shader, m_VertexArray);
		Hazel::Renderer::EndScene();
	}
	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}
	//按键事件
	void OnEvent(Hazel::Event& event) override
	{
		//Hazel::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}
	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& event)
	{
	}
private:
	Hazel::Ref<Hazel::Shader> m_Shader;
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;

	Hazel::Ref<Hazel::VertexArray> m_VertexArray;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::OrthoGraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraMovedSpeed;
	float m_CameraRotationSpeed;

	glm::vec3 m_SquarePosition;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}


