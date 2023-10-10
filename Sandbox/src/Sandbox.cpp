#include <Petal.h>

#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Cube1Position(0.5f), m_Cube1Transform(1.0f),
		  m_Cube2Position(-0.5f), m_Cube2Transform(1.0f),
		  m_DirLightDirection(1.0f, -1.0f, -1.0f), m_PointLight1Position(1.5f),
		  m_PointLight1Transform(
			  glm::translate(glm::mat4(1.0f), m_PointLight1Position)),
		  m_PointLight2Position(-1.5f),
		  m_PointLight2Transform(
			  glm::translate(glm::mat4(1.0f), m_PointLight2Position)),
		  m_DirLightAmbient(0.1), m_DirLightDiffuse(0.3f),
		  m_DirLightSpecular(1.0f), m_PointLight1Ambient(0.0f, 0.2f, 0.0f),
		  m_PointLight1Diffuse(0.1f, 0.5f, 0.1f), m_PointLight1Specular(1.0f),
		  m_PointLight2Ambient(0.2f, 0.0f, 0.0f),
		  m_PointLight2Diffuse(0.5f, 0.1f, 0.1f), m_PointLight2Specular(1.0f),
		  m_DirLight(
			  std::make_shared<ptl::DirectionalLight>(m_DirLightDirection,
				  m_DirLightAmbient, m_DirLightDiffuse, m_DirLightSpecular)),
		  m_PointLights(), m_CameraPos(0.0f, 0.0f, 5.0f),
		  m_CameraEuler(0.0f, -90.0f, 0.0f),
		  m_Camera(45.0f, 1280.0f, 720.0f, 0.1f, 100.0f)
	{
	}

	virtual void Init() override
	{
		// Cube setup
		float cubeVertices[8 * 24] = {-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, // Front
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f,
			0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f,

			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Back
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, -0.5f, 0.5f,
			-0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
			-1.0f, 0.0f, 1.0f,

			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Right
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f,
			1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Left
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f,
			0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, -1.0f,
			0.0f, 0.0f, 0.0f, 1.0f,

			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // Top
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, -0.5f,
			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.0f, 1.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f,
			0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f,
			-1.0f, 0.0f, 0.0f, 1.0f};

		const uint32_t nCubeIndices = 36;
		uint32_t cubeIndices[nCubeIndices] = {0, 1, 2, // Front
			2, 3, 0, 4, 5, 6,						   // Back
			6, 7, 4, 8, 9, 10,						   // Right
			10, 11, 8, 12, 13, 14,					   // Left
			14, 15, 12, 16, 17, 18,					   // Top
			18, 19, 16, 20, 21, 22,					   // Bottom
			22, 23, 20};

		m_CubeVA = ptl::VertexArray::Create();

		ptl::Ref<ptl::VertexBuffer> cubeVB =
			ptl::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
		cubeVB->Bind();

		std::vector<ptl::VertexBufferElement> cubeElements = {
			{ptl::ShaderDataType::Float3, "a_Position"},
			{ptl::ShaderDataType::Float3, "a_Normal"},
			{ptl::ShaderDataType::Float2, "a_TexCoords"}};
		ptl::VertexBufferLayout cubeLayout(cubeElements);

		cubeVB->SetLayout(cubeLayout);
		m_CubeVA->AddVertexBuffer(cubeVB);

		ptl::Ref<ptl::IndexBuffer> cubeIB =
			ptl::IndexBuffer::Create(cubeIndices, nCubeIndices);
		cubeIB->Bind();
		m_CubeVA->AddIndexBuffer(cubeIB);

		// Material setup

		m_CubeDiffuseTexture =
			ptl::Texture2D::Create("res/textures/crate_diffuse.png");
		m_CubeSpecularTexture =
			ptl::Texture2D::Create("res/textures/crate_specular.png");

		m_CubeMaterial = std::make_shared<ptl::PhongMaterial>(glm::vec3(0.5f),
			glm::vec3(0.5f), glm::vec3(0.5f), 32.0f);
		m_LampMaterial = std::make_shared<ptl::LampMaterial>(glm::vec3(1.0f));

		m_CubeMaterial->AddAmbientDiffuseMap(m_CubeDiffuseTexture, 0);
		m_CubeMaterial->EnableAmbientDiffuseMap();
		m_CubeMaterial->AddSpecularMap(m_CubeSpecularTexture, 1);
		m_CubeMaterial->EnableSpecularMap();

		// Light setup
		m_PointLights.push_back(std::make_shared<ptl::PointLight>(
			m_PointLight1Position, m_PointLight1Ambient, m_PointLight1Diffuse,
			m_PointLight1Specular, 1.0f, 0.09f, 0.032f));
		m_PointLights.push_back(std::make_shared<ptl::PointLight>(
			m_PointLight2Position, m_PointLight2Ambient, m_PointLight2Diffuse,
			m_PointLight2Specular, 1.0f, 0.09f, 0.032f));
	}

	virtual void ShutDown() override {}

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
		m_Cube1Transform = glm::translate(glm::mat4(1.0f), m_Cube1Position);
		m_Cube2Transform = glm::translate(glm::mat4(1.0f), m_Cube2Position);

		m_PointLight1Transform = glm::mat4(1.0f);
		m_PointLight1Transform =
			glm::translate(m_PointLight1Transform, m_PointLight1Position);
		m_PointLight1Transform =
			glm::scale(m_PointLight1Transform, glm::vec3(0.2f));

		m_PointLight2Transform = glm::mat4(1.0f);
		m_PointLight2Transform =
			glm::translate(m_PointLight2Transform, m_PointLight2Position);
		m_PointLight2Transform =
			glm::scale(m_PointLight2Transform, glm::vec3(0.2f));

		// Update lights
		m_DirLight->Direction = m_DirLightDirection;
		m_DirLight->Ambient = m_DirLightAmbient;
		m_DirLight->Diffuse = m_DirLightDiffuse;
		m_DirLight->Specular = m_DirLightSpecular;

		if (m_PointLights.size() > 0)
		{
			m_PointLights[0]->Position = m_PointLight1Position;
			m_PointLights[0]->Ambient = m_PointLight1Ambient;
			m_PointLights[0]->Diffuse = m_PointLight1Diffuse;
			m_PointLights[0]->Specular = m_PointLight1Specular;
		}

		if (m_PointLights.size() > 1)
		{
			m_PointLights[1]->Position = m_PointLight2Position;
			m_PointLights[1]->Ambient = m_PointLight2Ambient;
			m_PointLights[1]->Diffuse = m_PointLight2Diffuse;
			m_PointLights[1]->Specular = m_PointLight2Specular;
		}

		// Render
		ptl::Renderer::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene(m_Camera, m_PointLights, m_DirLight);

		ptl::Renderer::Submit(m_CubeVA, m_CubeMaterial, m_Cube1Transform);
		ptl::Renderer::Submit(m_CubeVA, m_CubeMaterial, m_Cube2Transform);

		m_LampMaterial->SetColor(m_PointLight1Diffuse);
		ptl::Renderer::Submit(m_CubeVA, m_LampMaterial, m_PointLight1Transform);
		m_LampMaterial->SetColor(m_PointLight2Diffuse);
		ptl::Renderer::Submit(m_CubeVA, m_LampMaterial, m_PointLight2Transform);

		ptl::Renderer::EndScene();
	}

	virtual void OnEvent(ptl::Event &event) override
	{
		ptl::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<ptl::MouseMoveEvent>(
			PTL_BIND_EVENT_FN(SandboxLayer::OnMouseMove));
		dispatcher.Dispatch<ptl::WindowResizeEvent>(
			PTL_BIND_EVENT_FN(SandboxLayer::OnWindowResize));
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Objects");
		ImGui::SliderFloat3("Cube 1 position", &m_Cube1Position.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Cube 2 position", &m_Cube2Position.x, -2.0f, 2.0f);
		ImGui::SliderFloat3("Dir light direction", &m_DirLightDirection.x,
			-2.0f, 2.0f);
		ImGui::SliderFloat3("Point light 1 position", &m_PointLight1Position.x,
			-2.0f, 2.0f);
		ImGui::SliderFloat3("Point light 2 position", &m_PointLight2Position.x,
			-2.0f, 2.0f);

		if (ImGui::Button("Enable diffuse map"))
			m_CubeMaterial->EnableAmbientDiffuseMap();
		if (ImGui::Button("Disable diffuse map"))
			m_CubeMaterial->DisableAmbientDiffuseMap();
		if (ImGui::Button("Enable specular map"))
			m_CubeMaterial->EnableSpecularMap();
		if (ImGui::Button("Disable specular map"))
			m_CubeMaterial->DisableSpecularMap();
		ImGui::End();

		ImGui::Begin("Lights");
		ImGui::ColorEdit3("Dir light ambient", &m_DirLightAmbient.x);
		ImGui::ColorEdit3("Dir light diffuse", &m_DirLightDiffuse.x);
		ImGui::ColorEdit3("Dir light specular", &m_DirLightSpecular.x);
		ImGui::ColorEdit3("Point light 1 ambient", &m_PointLight1Ambient.x);
		ImGui::ColorEdit3("Point light 1 diffuse", &m_PointLight1Diffuse.x);
		ImGui::ColorEdit3("Point light 1 specular", &m_PointLight1Specular.x);
		ImGui::ColorEdit3("Point light 2 ambient", &m_PointLight2Ambient.x);
		ImGui::ColorEdit3("Point light 2 diffuse", &m_PointLight2Diffuse.x);
		ImGui::ColorEdit3("Point light 2 specular", &m_PointLight2Specular.x);
		ImGui::End();

		ImGui::Begin("Camera");
		ImGui::SliderFloat3("Camera position", &m_CameraPos.x, -5.0f, 5.0f);
		ImGui::SliderFloat3("Camera rotation", &m_CameraEuler.x, -360.0f,
			360.0f);
		ImGui::End();
	}

private:
	bool OnMouseMove(ptl::MouseMoveEvent &event)
	{
		float x = event.GetXPos();
		float y = event.GetYPos();

		if (ptl::Input::IsMouseButtonPressed(ptl::MouseButtonCode::_2))
		{
			float deltaX = m_LastMouseX - x;
			float deltaY = y - m_LastMouseY;

			m_CameraEuler.y += deltaX * m_MouseSensitivity;
			m_CameraEuler.x += deltaY * m_MouseSensitivity;

			if (m_CameraEuler.x > 89.0f)
				m_CameraEuler.x = 89.0f;
			if (m_CameraEuler.x < -89.0f)
				m_CameraEuler.x = -89.0f;
		}
		m_LastMouseX = x;
		m_LastMouseY = y;
		return true;
	}

	bool OnWindowResize(ptl::WindowResizeEvent &event)
	{
		m_Camera.SetViewport((float)event.GetWidth(), (float)event.GetHeight());
		return false;
	}

private:
	// Geometry
	ptl::Ref<ptl::VertexArray> m_CubeVA;

	glm::vec3 m_Cube1Position;
	glm::mat4 m_Cube1Transform;

	glm::vec3 m_Cube2Position;
	glm::mat4 m_Cube2Transform;

	// Materials
	ptl::Ref<ptl::Texture2D> m_CubeDiffuseTexture;
	ptl::Ref<ptl::Texture2D> m_CubeSpecularTexture;

	ptl::Ref<ptl::PhongMaterial> m_CubeMaterial;
	ptl::Ref<ptl::LampMaterial> m_LampMaterial;

	// Lights
	glm::vec3 m_DirLightDirection;

	glm::vec3 m_PointLight1Position;
	glm::mat4 m_PointLight1Transform;

	glm::vec3 m_PointLight2Position;
	glm::mat4 m_PointLight2Transform;

	glm::vec3 m_DirLightAmbient;
	glm::vec3 m_DirLightDiffuse;
	glm::vec3 m_DirLightSpecular;

	glm::vec3 m_PointLight1Ambient;
	glm::vec3 m_PointLight1Diffuse;
	glm::vec3 m_PointLight1Specular;

	glm::vec3 m_PointLight2Ambient;
	glm::vec3 m_PointLight2Diffuse;
	glm::vec3 m_PointLight2Specular;

	ptl::Ref<ptl::DirectionalLight> m_DirLight;
	std::vector<ptl::Ref<ptl::PointLight>> m_PointLights;

	// Camera controller
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

	~Sandbox() {}
};

ptl::Application *ptl::CreateApplication()
{
	return new Sandbox();
}
