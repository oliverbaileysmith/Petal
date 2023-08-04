#include "ptlpch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glm/gtc/type_ptr.hpp>

namespace ptl
{
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = SplitShaders(source);
		Compile(shaderSources);

		// Get shader name from filepath
		size_t lastSlash = filepath.find_last_of("/\\");
		size_t start = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.');
		size_t count = lastDot == std::string::npos ? filepath.size() - start : lastDot - start;
		m_Name = filepath.substr(start, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
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

	const std::string& OpenGLShader::GetName() const
	{
		return m_Name;
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
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;

		std::ifstream ifs(filepath, std::ios::in | std::ios::binary);
		if (ifs)
		{
			// Move pointer to end of file and resize output string
			ifs.seekg(0, std::ios::end);
			result.resize(ifs.tellg());

			// Move pointer to beginning and read file
			ifs.seekg(0, std::ios::beg);
			ifs.read(&result[0], result.size());
			ifs.close();
		}
		else
		{
			PTL_CORE_ERROR("Could not open shader file \"{0}\"", filepath);
		}
		
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::SplitShaders(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		// Find first instance of #type
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		// Parse rest of file
		while (pos != std::string::npos)
		{
			// Find first new line character
			size_t eol = source.find_first_of("\r\n", pos);
			PTL_CORE_ASSERT(eol != std::string::npos, "Shader syntax error");

			// Set pointer to word after #type (this doesn't account for multiple whitespace)
			size_t begin = pos + typeTokenLength + 1;

			// Ensure valid shader type
			std::string type = source.substr(begin, eol - begin);
			PTL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			// Get source until next token or end of file
			size_t nextLinePos = source.find_first_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		PTL_CORE_ASSERT(shaderSources.size() < 3, "More than 2 shaders in file");

		// Create shader program and store in Shader class
		GLuint program = glCreateProgram();
		std::array<GLuint, 2> shaderIDs;

		int shaderIndex = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			// Create shader object
			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			// Test vertex shader compilation
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				PTL_CORE_ERROR("{0}", infoLog.data());
				PTL_CORE_ASSERT(false, "Failed to compile shader");
				break;
			}

			// If shader compilation succeeded, attach to program
			glAttachShader(program, shader);
			shaderIDs[shaderIndex++] = shader;
		}

		// Link program and test
		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (GLuint ID : shaderIDs)
			{
				glDeleteShader(ID);
			}

			PTL_CORE_ERROR("{0}", infoLog.data());
			PTL_CORE_ASSERT(false, "Failed to link shader program");
			return;
		}

		for (GLuint ID : shaderIDs)
		{
			glDetachShader(program, ID);
			glDeleteShader(ID);
		}

		m_ID = program;
	}

	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;

		PTL_CORE_ASSERT(false, "Unknown shader type");
		return 0;
	}

}