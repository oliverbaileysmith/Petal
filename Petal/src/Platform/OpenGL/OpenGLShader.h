#pragma once

#include <unordered_map>

#include <glad/glad.h>

#include "Petal/Renderer/Shader.h"

namespace ptl
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformBool(const std::string& name, bool value) const override;

		virtual void UploadUniformInt(const std::string& name, int32_t value) const override;
		virtual void UploadUniformInt2(const std::string& name, const glm::ivec2& value) const override;
		virtual void UploadUniformInt3(const std::string& name, const glm::ivec3& value) const override;
		virtual void UploadUniformInt4(const std::string& name, const glm::ivec4& value) const override;

		virtual void UploadUniformUint(const std::string& name, uint32_t value) const override;
		virtual void UploadUniformUint2(const std::string& name, const glm::uvec2& value) const override;
		virtual void UploadUniformUint3(const std::string& name, const glm::uvec3& value) const override;
		virtual void UploadUniformUint4(const std::string& name, const glm::uvec4& value) const override;

		virtual void UploadUniformFloat(const std::string& name, float value) const override;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& value) const override;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& value) const override;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& value) const override;

		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const override;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const override;

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> SplitShaders(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		static GLenum ShaderTypeFromString(const std::string& type);

	private:
		uint32_t m_ID;
	};
}
