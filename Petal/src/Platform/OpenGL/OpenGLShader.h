#pragma once

#include "Petal/Renderer/Shader.h"

namespace ptl
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& m) const override;

	private:
		uint32_t m_ID;
	};
}
