#include "ptlpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include "stb_image.h"

namespace ptl
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		// Load texture using stb_image
		int32_t width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PTL_CORE_ASSERT(data, "Failed to load image into texture");

		m_Width = width;
		m_Height = height;

		// Determine RGB or RGBA based on number of channels
		GLenum internalFormat = 0;
		GLenum dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		PTL_CORE_ASSERT(internalFormat && dataFormat, "Texture format not supported");

		// Allocate memory on GPU for texture
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		// Set min/mag filters
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Upload texture data to GPU
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

		// Unbind texture and free data from CPU
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		PTL_CORE_ASSERT(slot < 32, "Only texture slots 0-31 are supported");

		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}