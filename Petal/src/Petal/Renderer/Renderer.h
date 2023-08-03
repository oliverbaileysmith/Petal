#pragma once

#include "Petal/Core.h"

#include "Petal/Renderer/RendererAPI.h"
#include "Petal/Renderer/Camera.h"

namespace ptl
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform);

		// Renderer API commands
		inline static void Init() { s_RendererAPI->Init(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }

		inline static void DrawIndexed(const Ref<VertexArray> vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }

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
