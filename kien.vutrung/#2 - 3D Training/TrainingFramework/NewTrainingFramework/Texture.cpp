#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/TGA.h"


Texture::Texture(const char* filename)
{
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	int iWidth, iHeight, iBpp;
	auto *imageData = LoadTGA(filename, &iWidth, &iHeight, &iBpp);
	auto internalformat = (iBpp == 32) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	delete[] imageData;
	m_Target = GL_TEXTURE_2D;
}

Texture::Texture(std::vector<const char*> faces)
{
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureId);
	for (int i = 0; i < 6; i++)
	{
		int iWidth, iHeight, iBpp;
		auto* imageData = LoadTGA(faces[i], &iWidth, &iHeight, &iBpp);
		auto internalformat = (iBpp == 32) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalformat, iWidth, iHeight, 0, internalformat, GL_UNSIGNED_BYTE, imageData);
		delete[] imageData;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	m_Target = GL_TEXTURE_CUBE_MAP;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureId);
}

GLuint Texture::GetTextureId() const
{
	return m_TextureId;
}

GLenum Texture::GetTarget() const
{
	return m_Target;
}
