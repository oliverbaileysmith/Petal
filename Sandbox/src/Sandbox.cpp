#include <Petal.h>

#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Camera(45.0f, 1280.0f, 720.0f, 0.1f, 100.0f),
		m_CubePosition(0.0f), m_CubeTransform(1.0f), m_CubeColor(1.0f, 1.0f, 0.0f),
		m_LightPosition(2.0f), m_LightTransform(glm::translate(glm::mat4(1.0f), m_LightPosition)), m_LightColor(1.0f),
		m_CameraPos(0.0f, 0.0f, 3.0f), m_CameraEuler(0.0f, -90.0f, 0.0f)
	{

	}

	virtual void Init() override
	{
		// Cube setup
		float cubeVertices[3 * 8] = {
			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			 0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f
		};

		const uint32_t nCubeIndices = 36;
		uint32_t cubeIndices[nCubeIndices] = {
			0, 1, 2, // Front
			2, 3, 0,
			4, 5, 6, // Back
			6, 7, 4,
			1, 4, 7, // Right
			7, 2, 1,
			5, 0, 3, // Left
			3, 6, 5,
			3, 2, 7, // Top
			7, 6, 3,
			5, 4, 1, // Bottom
			1, 0, 5
		};

		m_CubeVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> cubeVB = ptl::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
		cubeVB->Bind();

		std::vector<ptl::VertexBufferElement> cubeElements = {
			{ptl::ShaderDataType::Float3, "a_Position"}
		};
		ptl::VertexBufferLayout cubeLayout(cubeElements);

		cubeVB->SetLayout(cubeLayout);
		m_CubeVA->AddVertexBuffer(cubeVB);

		ptl::Ref<ptl::IndexBuffer> cubeIB = ptl::IndexBuffer::Create(cubeIndices, nCubeIndices);
		cubeIB->Bind();
		m_CubeVA->AddIndexBuffer(cubeIB);

		// Light setup

		m_LightVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> lightVB = ptl::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
		lightVB->Bind();

		std::vector<ptl::VertexBufferElement> lightElements = {
			{ptl::ShaderDataType::Float3, "a_Position"}
		};
		ptl::VertexBufferLayout lightLayout(lightElements);

		lightVB->SetLayout(lightLayout);
		m_LightVA->AddVertexBuffer(lightVB);

		ptl::Ref<ptl::IndexBuffer> lightIB = ptl::IndexBuffer::Create(cubeIndices, nCubeIndices);
		lightIB->Bind();
		m_LightVA->AddIndexBuffer(cubeIB);

		ptl::Ref<ptl::Shader> textureShader = m_ShaderLibrary.Load("res/shaders/Texture.glsl");
		ptl::Ref<ptl::Shader> phongShader = m_ShaderLibrary.Load("res/shaders/Phong.glsl");
		ptl::Ref<ptl::Shader> lampShader = m_ShaderLibrary.Load("res/shaders/Lamp.glsl");

		m_TestTexture = ptl::Texture2D::Create("res/textures/test.png");
		m_SusTexture = ptl::Texture2D::Create("res/textures/sus.png");

		textureShader->Bind();
		m_TestTexture->Bind(0);
		m_SusTexture->Bind(1);
	}

	virtual void ShutDown() override
	{

	}

	virtual void OnUpdate(ptl::Timestep timestep) override
	{
		// Process input
		glm::vec3 forward = m_Camera.Front();
		forward.y = 0.0f;
		forward = glm::normalize(forward);
		glm::vec3 right = glm::normalize(m_Camera.Right());
		glm::vec3 up(0.0f, 1.0f, 0.0f);

		if (ptl::Input::IsKeyPressed(ptl::KeyCode::A))
		{
			m_CameraPos -= right * timestep.GetSeconds();
		}
		if (ptl::Input::IsKeyPressed(ptl::KeyCode::D))
		{
			m_CameraPos += right * timestep.GetSeconds();
		}
		if (ptl::Input::IsKeyPressed(ptl::KeyCode::S))
		{
			m_CameraPos -= forward * timestep.GetSeconds();
		}
		if (ptl::Input::IsKeyPressed(ptl::KeyCode::W))
		{
			m_CameraPos += forward * timestep.GetSeconds();
		}
		if (ptl::Input::IsKeyPressed(ptl::KeyCode::LEFT_SHIFT))
		{
			m_CameraPos -= up * timestep.GetSeconds();
		}
		if (ptl::Input::IsKeyPressed(ptl::KeyCode::SPACE))
		{
			m_CameraPos += up * timestep.GetSeconds();
		}

		m_Camera.SetPosition(m_CameraPos);
		m_Camera.SetEuler(m_CameraEuler);
		m_Camera.Update();

		// Update geometry
		m_CubeTransform = glm::translate(glm::mat4(1.0f), m_CubePosition);
		m_LightTransform = glm::translate(glm::mat4(1.0f), m_LightPosition);

		// Render
		ptl::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene(m_Camera);

		ptl::Ref<ptl::Shader> textureShader = m_ShaderLibrary.Get("Texture");
		ptl::Ref<ptl::Shader> phongShader = m_ShaderLibrary.Get("Phong");
		ptl::Ref<ptl::Shader> lampShader = m_ShaderLibrary.Get("Lamp");

		phongShader->Bind();
		phongShader->UploadUniformFloat3("u_ObjectColor", m_CubeColor);
		phongShader->UploadUniformFloat3("u_LightColor", m_LightColor);
		ptl::Renderer::Submit(m_CubeVA, phongShader, m_CubeTransform);

		lampShader->Bind();
		lampShader->UploadUniformFloat3("u_LightColor", m_LightColor);
		ptl::Renderer::Submit(m_LightVA, lampShader, m_LightTransform);

		ptl::Renderer::EndScene();
	}

	virtual void OnEvent(ptl::Event& event) override
	{
		ptl::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<ptl::MouseMoveEvent>(PTL_BIND_EVENT_FN(SandboxLayer::OnMouseMove));
		dispatcher.Dispatch<ptl::WindowResizeEvent>(PTL_BIND_EVENT_FN(SandboxLayer::OnWindowResize));
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Controls");

		ImGui::SliderFloat3("Cube Position", &m_CubePosition.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Light Position", &m_LightPosition.x, -2.0f, 2.0f);

		ImGui::ColorEdit3("Cube Color", &m_CubeColor.x);
		ImGui::ColorEdit3("Light Color", &m_LightColor.x);

		ImGui::SliderFloat3("Camera Position", &m_CameraPos.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera Rotation", &m_CameraEuler.x, -360.0f, 360.0f);

		ImGui::End();
	}

private:
	bool OnMouseMove(ptl::MouseMoveEvent& event)
	{
		float x = event.GetXPos();
		float y = event.GetYPos();

		if (ptl::Input::IsMouseButtonPressed(ptl::MouseButtonCode::_2))
		{
			float deltaX = m_LastMouseX - x;
			float deltaY = y - m_LastMouseY;

			m_CameraEuler.y += deltaX * m_MouseSensitivity;
			m_CameraEuler.x += deltaY * m_MouseSensitivity;

			if (m_CameraEuler.x > 89.0f) m_CameraEuler.x = 89.0f;
			if (m_CameraEuler.x < -89.0f) m_CameraEuler.x = -89.0f;
		}
		m_LastMouseX = x;
		m_LastMouseY = y;
		return true;
	}

	bool OnWindowResize(ptl::WindowResizeEvent& event)
	{
		m_Camera.SetViewport((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}

private:
	ptl::ShaderLibrary m_ShaderLibrary;

	ptl::Ref<ptl::Texture2D> m_TestTexture;
	ptl::Ref<ptl::Texture2D> m_SusTexture;

	ptl::Ref<ptl::VertexArray> m_CubeVA;
	ptl::Ref<ptl::VertexArray> m_LightVA;

	glm::vec3 m_CubePosition;
	glm::mat4 m_CubeTransform;
	glm::vec3 m_CubeColor;

	glm::vec3 m_LightPosition;
	glm::mat4 m_LightTransform;
	glm::vec3 m_LightColor;

	float m_MouseSensitivity = 0.1f;
	float m_LastMouseX = 640;
	float m_LastMouseY = 360;
	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraEuler;
	ptl::Camera m_Camera;
};

class Sandbox : public ptl::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};

ptl::Application* ptl::CreateApplication()
{
	return new Sandbox();
}