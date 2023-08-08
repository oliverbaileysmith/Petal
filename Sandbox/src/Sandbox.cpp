#include <Petal.h>

#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Camera(45.0f, 1280.0f, 720.0f, 0.1f, 100.0f),
		m_SquarePosition(0.0f), m_Square1Transform(1.0f), m_Square2Transform(1.0f),
		m_TrianglePosition(0.0f), m_TriangleColor(1.0f), m_TriangleTransform(1.0f),
		m_CameraPos(0.0f, 0.0f, 1.0f), m_CameraEuler(0.0f, -90.0f, 0.0f)
	{

	}

	virtual void Init() override
	{
		// Square setup
		float squareVertices[4 * 9] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		const uint32_t nSquareIndices = 6;
		uint32_t squareIndices[nSquareIndices] = {
			0, 1, 2,
			2, 3, 0
		};

		m_SquareVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> squareVertexBuffer = ptl::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVertexBuffer->Bind();

		std::vector<ptl::VertexBufferElement> squareElements = {
			{ptl::ShaderDataType::Float3, "a_Position"},
			{ptl::ShaderDataType::Float4, "a_Color"},
			{ptl::ShaderDataType::Float2, "a_TexCoords"}
		};
		ptl::VertexBufferLayout squareLayout(squareElements);

		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		ptl::Ref<ptl::IndexBuffer> squareIndexBuffer = ptl::IndexBuffer::Create(squareIndices, nSquareIndices);
		squareIndexBuffer->Bind();
		m_SquareVA->AddIndexBuffer(squareIndexBuffer);

		// Triangle setup
		float triangleVertices[3 * 3] = {
			-0.25f, -0.25f, 0.0f,
			 0.25f, -0.25f, 0.0f,
			 0.0f,   0.25f, 0.0f
		};

		const uint32_t nTriangleIndices = 3;
		uint32_t triangleIndices[nTriangleIndices] = {
			0, 1, 2
		};

		m_TriangleVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> triangleVertexBuffer = ptl::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
		triangleVertexBuffer->Bind();

		std::vector<ptl::VertexBufferElement> triangleElements = {
			{ptl::ShaderDataType::Float3, "a_Position"}
		};
		ptl::VertexBufferLayout triangleLayout(triangleElements);

		triangleVertexBuffer->SetLayout(triangleLayout);
		m_TriangleVA->AddVertexBuffer(triangleVertexBuffer);

		ptl::Ref<ptl::IndexBuffer> triangleIndexBuffer = ptl::IndexBuffer::Create(triangleIndices, nTriangleIndices);
		triangleIndexBuffer->Bind();
		m_TriangleVA->AddIndexBuffer(triangleIndexBuffer);

		std::string flatColorVertexSource = R"(
			#version 460 core
			
			layout (location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProj;
			uniform mat4 u_Model;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
			}
		)";

		std::string flatColorFragmentSource = R"(
			#version 460 core
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_ShaderLibrary.Add(ptl::Shader::Create("FlatColor", flatColorVertexSource, flatColorFragmentSource));
		ptl::Ref<ptl::Shader> textureShader = m_ShaderLibrary.Load("res/shaders/Texture.glsl");

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
		m_Square1Transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		m_TriangleTransform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);

		// Render
		ptl::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene(m_Camera);

		ptl::Ref<ptl::Shader> textureShader = m_ShaderLibrary.Get("Texture");
		ptl::Ref<ptl::Shader> flatColorShader = m_ShaderLibrary.Get("FlatColor");

		textureShader->Bind();
		textureShader->UploadUniformInt("u_Texture", 0);
		ptl::Renderer::Submit(m_SquareVA, textureShader, m_Square1Transform);

		textureShader->Bind();
		textureShader->UploadUniformInt("u_Texture", 1);
		ptl::Renderer::Submit(m_SquareVA, textureShader, m_Square2Transform);

		flatColorShader->Bind();
		flatColorShader->UploadUniformFloat3("u_Color", m_TriangleColor);
		ptl::Renderer::Submit(m_TriangleVA, flatColorShader, m_TriangleTransform);

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

		ImGui::SliderFloat3("Square Position", &m_SquarePosition.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Triangle Position", &m_TrianglePosition.x, -1.0f, 1.0f);
		ImGui::ColorEdit3("Triangle Color", &m_TriangleColor.x);

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
		m_Camera.SetViewport(event.GetWidth(), event.GetHeight());
		return false;
	}

private:
	ptl::ShaderLibrary m_ShaderLibrary;

	ptl::Ref<ptl::Texture2D> m_TestTexture;
	ptl::Ref<ptl::Texture2D> m_SusTexture;

	ptl::Ref<ptl::VertexArray> m_SquareVA;
	ptl::Ref<ptl::VertexArray> m_TriangleVA;

	glm::vec3 m_SquarePosition;
	glm::mat4 m_Square1Transform;
	glm::mat4 m_Square2Transform;

	glm::vec3 m_TrianglePosition;
	glm::vec3 m_TriangleColor;
	glm::mat4 m_TriangleTransform;

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