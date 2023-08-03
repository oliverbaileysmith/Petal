#include "ptlpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace ptl
{
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		// Create vertex shader object
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		// Test vertex shader compilation
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			PTL_CORE_ERROR("{0}", infoLog.data());
			PTL_CORE_ASSERT(false, "Failed to compile vertex shader");
			return;
		}

		// Create vertex shader object
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		// Test fragment shader compilation
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			PTL_CORE_ERROR("{0}", infoLog.data());
			PTL_CORE_ASSERT(false, "Failed to compile fragment shader");
			return;
		}

		// Create shader program and store in Shader class
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);
		glLinkProgram(m_ID);

		// Test program linking
		GLint isLinked = 0;
		glGetProgramiv(m_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PTL_CORE_ERROR("{0}", infoLog.data());
			PTL_CORE_ASSERT(false, "Failed to link shader program");
			return;
		}

		glDetachShader(m_ID, vertexShader);
		glDetachShader(m_ID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformBool(const std::string& name, bool value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform1i(loc, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform1f(loc, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform2f(loc, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform3f(loc, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int32_t value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform1i(loc, value);
	}

	void OpenGLShader::UploadUniformInt2(const std::string& name, const glm::ivec2& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform2i(loc, value.x, value.y);
	}

	void OpenGLShader::UploadUniformInt3(const std::string& name, const glm::ivec3& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform3i(loc, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformInt4(const std::string& name, const glm::ivec4& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform4i(loc, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformUint(const std::string& name, uint32_t value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform1ui(loc, value);
	}

	void OpenGLShader::UploadUniformUint2(const std::string& name, const glm::uvec2& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform2ui(loc, value.x, value.y);
	}

	void OpenGLShader::UploadUniformUint3(const std::string& name, const glm::uvec3& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform3ui(loc, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformUint4(const std::string& name, const glm::uvec4& value) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniform4ui(loc, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) const
	{
		int loc = glGetUniformLocation(m_ID, name.c_str());
		PTL_CORE_ASSERT(loc != -1, "Invalid uniform location");

		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}