#include <Petal.h>

#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Camera(45.0f, 1280.0f, 720.0f, 0.1f, 100.0f),
		m_CubePosition(0.0f), m_CubeTransform(1.0f),
		m_Cube2Position(-1.0f), m_Cube2Transform(1.0f),
		m_PointLightPosition(1.0f), m_PointLightTransform(glm::translate(glm::mat4(1.0f), m_PointLightPosition)),
		m_PointLightAmbient(glm::vec3(0.1f, 0.2f, 0.1f)), m_PointLightDiffuse(glm::vec3(0.1f, 0.4f, 0.1f)), m_PointLightSpecular(1.0f),
		m_DirLight(std::make_shared<ptl::DirectionalLight>(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.1f), glm::vec3(0.3f), glm::vec3(1.0f, 1.0f, 1.0f))),
		m_PointLights(), m_CameraPos(0.0f, 0.0f, 3.0f), m_CameraEuler(0.0f, -90.0f, 0.0f)
	{

	}

	virtual void Init() override
	{
		// Cube setup
		float cubeVertices[8 * 24] = {
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // Front
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,

			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // Back
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,

			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // Right
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // Left
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f, // Top
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // Bottom
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f
		};

		const uint32_t nCubeIndices = 36;
		uint32_t cubeIndices[nCubeIndices] = {
			 0,  1,  2, // Front
			 2,  3,  0,
			 4,  5,  6, // Back
			 6,  7,  4,
			 8,  9, 10, // Right
			10, 11,  8,
			12, 13, 14, // Left
			14, 15, 12,
			16, 17, 18, // Top
			18, 19, 16,
			20, 21, 22, // Bottom
			22, 23, 20
		};

		m_CubeVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> cubeVB = ptl::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
		cubeVB->Bind();

		std::vector<ptl::VertexBufferElement> cubeElements = {
			{ptl::ShaderDataType::Float3, "a_Position"},
			{ptl::ShaderDataType::Float3, "a_Normal"},
			{ptl::ShaderDataType::Float2, "a_TexCoords"}
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

		lightVB->SetLayout(cubeLayout);
		m_LightVA->AddVertexBuffer(lightVB);

		ptl::Ref<ptl::IndexBuffer> lightIB = ptl::IndexBuffer::Create(cubeIndices, nCubeIndices);
		lightIB->Bind();
		m_LightVA->AddIndexBuffer(cubeIB);

		ptl::Ref<ptl::Shader> textureShader = ptl::Renderer::GetShaderLibrary()->Load("res/shaders/Texture.glsl");

		m_CubeDiffuseSlot = 0;
		m_CubeSpecularSlot = 1;

		m_CubeMaterial = std::make_shared<ptl::MappedPhongMaterial>(m_CubeDiffuseSlot, m_CubeSpecularSlot, 32.0f);
		m_LampMaterial = std::make_shared<ptl::LampMaterial>(m_PointLightDiffuse);

		m_CubeDiffuseTexture = ptl::Texture2D::Create("res/textures/crate_diffuse.png");
		m_CubeSpecularTexture = ptl::Texture2D::Create("res/textures/crate_specular.png");
		m_SampleTexture = ptl::Texture2D::Create("res/textures/test.png");

		m_CubeMaterial->Bind();
		
		m_PointLights.push_back(std::make_shared<ptl::PointLight>(m_PointLightPosition, m_PointLightAmbient, m_PointLightDiffuse, m_PointLightSpecular, 1.0f, 0.09f, 0.032f));
		m_PointLights.push_back(std::make_shared<ptl::PointLight>(glm::vec3(-2.0f), glm::vec3(0.1f, 0.0f, 0.0f), glm::vec3(0.4f, 0.1f, 0.1f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f));
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
		m_Cube2Transform = glm::translate(glm::mat4(1.0f), m_Cube2Position);
		m_PointLightTransform = glm::mat4(1.0f);
		m_PointLightTransform = glm::translate(m_PointLightTransform, m_PointLightPosition);
		m_PointLightTransform = glm::scale(m_PointLightTransform, glm::vec3(0.2f));
		m_PointLights[0] = std::make_shared<ptl::PointLight>(m_PointLightPosition, m_PointLightAmbient, m_PointLightDiffuse, m_PointLightSpecular, 1.0f, 0.09f, 0.032f);

		glm::mat4 pointLight2Transform = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f));
		pointLight2Transform = glm::scale(pointLight2Transform, glm::vec3(0.2f));

		// Render
		ptl::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene(m_Camera, m_DirLight, m_PointLights);

		m_CubeMaterial->Bind();
		m_CubeMaterial->SetAmbientDiffuseSlot(m_CubeDiffuseSlot);
		m_CubeMaterial->SetSpecularSlot(m_CubeSpecularSlot);

		m_CubeDiffuseTexture->Bind(m_CubeDiffuseSlot);
		m_CubeSpecularTexture->Bind(m_CubeSpecularSlot);

		ptl::Renderer::Submit(m_CubeVA, m_CubeMaterial, m_CubeTransform);
		ptl::Renderer::Submit(m_CubeVA, m_CubeMaterial, m_Cube2Transform);

		m_LampMaterial->SetColor(m_PointLightDiffuse);
		ptl::Renderer::Submit(m_LightVA, m_LampMaterial, m_PointLightTransform);
		m_LampMaterial->SetColor(glm::vec3(0.5f, 0.2f, 0.2f));
		ptl::Renderer::Submit(m_LightVA, m_LampMaterial, pointLight2Transform);

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
		ImGui::Begin("Camera");
		ImGui::SliderFloat3("Camera position", &m_CameraPos.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera rotation", &m_CameraEuler.x, -360.0f, 360.0f);
		ImGui::End();

		ImGui::Begin("Object Positions");
		ImGui::SliderFloat3("Cube position", &m_CubePosition.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Point light 1 position", &m_PointLightPosition.x, -2.0f, 2.0f);
		ImGui::End();

		ImGui::Begin("Object Colors");
		ImGui::SliderFloat3("Point light 1 ambient", &m_PointLightAmbient.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point light 1 diffuse", &m_PointLightDiffuse.x, 0.0f, 1.0f);
		ImGui::SliderFloat3("Point light 1 specular", &m_PointLightSpecular.x, 0.0f, 1.0f);
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
	ptl::Ref<ptl::Texture2D> m_CubeDiffuseTexture;
	ptl::Ref<ptl::Texture2D> m_CubeSpecularTexture;
	ptl::Ref<ptl::Texture2D> m_SampleTexture;

	ptl::Ref<ptl::VertexArray> m_CubeVA;
	ptl::Ref<ptl::VertexArray> m_LightVA;

	glm::vec3 m_CubePosition;
	glm::mat4 m_CubeTransform;

	glm::vec3 m_Cube2Position;
	glm::mat4 m_Cube2Transform;

	uint32_t m_CubeDiffuseSlot;
	uint32_t m_CubeSpecularSlot;

	glm::vec3 m_PointLightPosition;
	glm::mat4 m_PointLightTransform;

	glm::vec3 m_PointLightAmbient;
	glm::vec3 m_PointLightDiffuse;
	glm::vec3 m_PointLightSpecular;

	ptl::Ref<ptl::DirectionalLight> m_DirLight;
	std::vector<ptl::Ref<ptl::PointLight>> m_PointLights;
	ptl::Ref<ptl::MappedPhongMaterial> m_CubeMaterial;
	ptl::Ref<ptl::LampMaterial> m_LampMaterial;

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