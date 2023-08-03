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
		
		virtual void UploadUniformBool(const std::string& name, bool value) const = 0;

		virtual void UploadUniformInt(const std::string& name, int32_t value) const = 0;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& value) const = 0;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& value) const = 0;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& value) const = 0;

		virtual void UploadUniformUint(const std::string& name, uint32_t value) const = 0;
		virtual void UploadUniformUint2(const std::string& name, const glm::uvec2& value) const = 0;
		virtual void UploadUniformUint3(const std::string& name, const glm::uvec3& value) const = 0;
		virtual void UploadUniformUint4(const std::string& name, const glm::uvec4& value) const = 0;

		virtual void UploadUniformFloat(const std::string& name, float value) const = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const = 0;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const = 0;

		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
		static uint32_t GetSizeOfShaderDataType(ShaderDataType type);
	};
}
