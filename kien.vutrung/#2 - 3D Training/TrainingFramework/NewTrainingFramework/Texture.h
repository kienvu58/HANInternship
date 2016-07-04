#pragma once
#include "../Utilities/esUtil.h"
#include <vector>

class Texture
{
public:
	~Texture();
	explicit Texture(const char* filename);
	explicit Texture(std::vector<const char *> faces);
	GLuint GetTextureId() const;
	GLenum GetTarget() const;
private:
	GLuint m_TextureId;
	GLenum m_Target;
};
