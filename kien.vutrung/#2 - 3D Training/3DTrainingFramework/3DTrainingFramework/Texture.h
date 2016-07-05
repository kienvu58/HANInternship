#pragma once
#include "../Utilities/esUtil.h"

class Texture
{
public:
	Texture();
	~Texture();
	void LoadTexture(const char * filename, GLenum tiling);
	void LoadTexture(const char ** filename, GLenum tiling);
	GLuint GetTextureId() const;
	GLenum GetTarget() const;
	int GetId() const;
	void SetId(int id);
private:
	int m_Id;
	GLuint m_TextureId;
	GLenum m_Target;
};
