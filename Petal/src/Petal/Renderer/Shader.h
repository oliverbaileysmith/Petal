#pragma once

#include <string>

#include <glm/glm.hpp>

namespace ptl
{
	enum class ShaderDataType
	{
		None,
		Bool,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4
	};

	class Shader
	{
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& m) const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		static uint32_t GetSizeOfShaderDataType(ShaderDataType type);
	};
}
