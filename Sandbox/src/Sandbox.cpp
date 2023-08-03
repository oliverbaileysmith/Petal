#include <Petal.h>

#include <glm/gtc/matrix_transform.hpp>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Camera(45.0f, 1280.0f, 720.0f, 0.1f, 100.0f),
		m_SquarePosition(0.0f), m_SquareTransform(1.0f), m_TrianglePosition(0.0f), m_TriangleColor(1.0f), m_TriangleTransform(1.0f)
	{
		
	}

	virtual void Init() override
	{
		// Square setup
		float squareVertices[4 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		const uint32_t nSquareIndices = 6;
		uint32_t squareIndices[nSquareIndices] = {
			0, 1, 2,
			2, 3, 0
		};

		m_SquareVA = std::shared_ptr<ptl::VertexArray>(ptl::VertexArray::Create());

		std::shared_ptr<ptl::VertexBuffer> squareVertexBuffer = std::shared_ptr<ptl::VertexBuffer>(ptl::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVertexBuffer->Bind();

		std::vector<ptl::VertexBufferElement> squareElements = {
			{ptl::ShaderDataType::Float3, "a_Position"},
			{ptl::ShaderDataType::Float4, "a_Color"}
		};
		ptl::VertexBufferLayout squareLayout(squareElements);

		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		std::shared_ptr<ptl::IndexBuffer> squareIndexBuffer = std::shared_ptr<ptl::IndexBuffer>(ptl::IndexBuffer::Create(squareIndices, nSquareIndices));
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

		m_TriangleVA = std::shared_ptr<ptl::VertexArray>(ptl::VertexArray::Create());

		std::shared_ptr<ptl::VertexBuffer> triangleVertexBuffer = std::shared_ptr<ptl::VertexBuffer>(ptl::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		triangleVertexBuffer->Bind();

		std::vector<ptl::VertexBufferElement> triangleElements = {
			{ptl::ShaderDataType::Float3, "a_Position"}
		};
		ptl::VertexBufferLayout triangleLayout(triangleElements);

		triangleVertexBuffer->SetLayout(triangleLayout);
		m_TriangleVA->AddVertexBuffer(triangleVertexBuffer);

		std::shared_ptr<ptl::IndexBuffer> triangleIndexBuffer = std::shared_ptr<ptl::IndexBuffer>(ptl::IndexBuffer::Create(triangleIndices, nTriangleIndices));
		triangleIndexBuffer->Bind();
		m_TriangleVA->AddIndexBuffer(triangleIndexBuffer);

		std::string genericVertexSource = R"(
			#version 460 core
			
			layout (location = 0) in vec3 a_Position;
			layout (location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProj;
			uniform mat4 u_Model;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
			}
		)";

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

		std::string genericFragmentSource = R"(
			#version 460 core
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
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

		m_GenericShader = std::shared_ptr<ptl::Shader>(ptl::Shader::Create(genericVertexSource, genericFragmentSource));
		m_FlatColorShader = std::shared_ptr<ptl::Shader>(ptl::Shader::Create(flatColorVertexSource, flatColorFragmentSource));
	}

	virtual void ShutDown() override
	{

	}

	virtual void OnUpdate(ptl::Timestep timestep) override
	{
		m_SquareTransform = glm::translate(glm::mat4(1.0f), m_SquarePosition);
		m_TriangleTransform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);

		ptl::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene(m_Camera);

		ptl::Renderer::Submit(m_SquareVA, m_GenericShader, m_SquareTransform);
		m_FlatColorShader->Bind();
		m_FlatColorShader->UploadUniformFloat3("u_Color", m_TriangleColor);
		ptl::Renderer::Submit(m_TriangleVA, m_FlatColorShader, m_TriangleTransform);

		ptl::Renderer::EndScene();
	}

	virtual void OnEvent(ptl::Event& event) override
	{
		PTL_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Controls");
		ImGui::SliderFloat3("Square Position", &m_SquarePosition.x, -1.0f, 1.0f);
		ImGui::SliderFloat3("Triangle Position", &m_TrianglePosition.x, -1.0f, 1.0f);
		ImGui::ColorEdit3("Triangle Color", &m_TriangleColor.x);
		ImGui::End();
	}

private:
	std::shared_ptr<ptl::Shader> m_GenericShader;
	std::shared_ptr<ptl::Shader> m_FlatColorShader;
	std::shared_ptr<ptl::VertexArray> m_SquareVA;
	std::shared_ptr<ptl::VertexArray> m_TriangleVA;

	glm::vec3 m_SquarePosition;
	glm::mat4 m_SquareTransform;

	glm::vec3 m_TrianglePosition;
	glm::vec3 m_TriangleColor;
	glm::mat4 m_TriangleTransform;

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