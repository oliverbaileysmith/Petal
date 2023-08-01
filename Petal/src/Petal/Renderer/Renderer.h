#pragma once

#include "Petal/Renderer/RendererAPI.h"
#include "Petal/Renderer/Camera.h"

namespace ptl
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		// Renderer API commands
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const std::shared_ptr<VertexArray> vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProj;
		};

		static RendererAPI* s_RendererAPI;
		static SceneData* s_SceneData;
	};
}
