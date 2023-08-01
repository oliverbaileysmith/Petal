#include <Petal.h>

class SandboxLayer : public ptl::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox")
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
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0f);
			}
		)";

		std::string magentaVertexSource = R"(
			#version 460 core
			
			layout (location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0f);
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

		std::string magentaFragmentSource = R"(
			#version 460 core
			
			layout (location = 0) out vec4 color;
			
			in vec3 v_Position;
			
			void main()
			{
				color = vec4(1.0f, 0.0f, 1.0f, 1.0f);
			}
		)";

		m_GenericShader = std::shared_ptr<ptl::Shader>(ptl::Shader::Create(genericVertexSource, genericFragmentSource));
		m_MagentaShader = std::shared_ptr<ptl::Shader>(ptl::Shader::Create(magentaVertexSource, magentaFragmentSource));
	}

	virtual void ShutDown() override
	{

	}

	virtual void OnUpdate() override
	{
		ptl::Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		ptl::Renderer::Clear();

		ptl::Renderer::BeginScene();

		m_GenericShader->Bind();
		ptl::Renderer::Submit(m_SquareVA);

		m_MagentaShader->Bind();
		ptl::Renderer::Submit(m_TriangleVA);

		ptl::Renderer::EndScene();
	}

	virtual void OnEvent(ptl::Event& event) override
	{
		PTL_TRACE("{0}", event);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello");
		ImGui::End();
	}

private:
	std::shared_ptr<ptl::Shader> m_GenericShader;
	std::shared_ptr<ptl::Shader> m_MagentaShader;
	std::shared_ptr<ptl::VertexArray> m_SquareVA;
	std::shared_ptr<ptl::VertexArray> m_TriangleVA;
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