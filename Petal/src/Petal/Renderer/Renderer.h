#pragma once

#include "Petal/Core/Core.h"

#include "Petal/Renderer/RendererAPI.h"
#include "Petal/Renderer/Camera.h"
#include "Petal/Renderer/Material.h"
#include "Petal/Renderer/Light.h"

namespace ptl
{
	class Renderer
	{
	public:
		static void BeginScene(Camera &camera,
			const std::vector<Ref<PointLight>> &pointLights,
			const Ref<DirectionalLight> &dirLight = nullptr);
		static void EndScene();

		static void OnWindowResize(uint32_t width, uint32_t height);
		static void Submit(const Ref<VertexArray> &vertexArray,
			const Ref<Material> &material, const glm::mat4 &transform);

		inline static ShaderLibrary *GetShaderLibrary()
		{
			return s_ShaderLibrary;
		}

		// Renderer API commands
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void SetViewport(uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(width, height);
		}
		inline static void SetClearColor(const glm::vec4 &color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray> vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}

	private:
		struct SceneData
		{
			glm::mat4 ViewProj;
			glm::vec3 CameraPosition;

			bool DirLightEnabled;
			Ref<DirectionalLight> DirLight;
			std::vector<Ref<PointLight>> PointLights;

			SceneData() {}
		};

		static RendererAPI *s_RendererAPI;
		static ShaderLibrary *s_ShaderLibrary;
		static SceneData *s_SceneData;
	};
} // namespace ptl
