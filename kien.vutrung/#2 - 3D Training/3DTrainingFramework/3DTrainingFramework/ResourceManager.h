#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"

class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	int Initialize(const char* filename);
private:
	ResourceManager();
	int m_NModels;
	Model** m_ModelList;
	int m_NTextures;
	Texture** m_TextureList;
	int m_NShaders;
	Shaders** m_ShaderList;
	static ResourceManager* s_Instance;
	static GLenum GetWrappingMode(const char* wrappingMode);
	static GLenum GetShaderState(const char* state);
};
