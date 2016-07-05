#include "stdafx.h"
#include "ResourceManager.h"

#define LENGTH	80	
ResourceManager* ResourceManager::s_Instance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new ResourceManager();
	}
	return s_Instance;
}


int ResourceManager::Initialize(const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (f)
	{
		// Read models information
		fscanf(f, "#Models: %d\n", &m_NModels);
		m_ModelList = new Model*[m_NModels];
		for (int i = 0; i < m_NModels; i++)
		{
			char path[LENGTH] = "../Resources/";
			int id = 19;
			char file[LENGTH];
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "FILE %s\n", file);
			strcat(path, file);
			m_ModelList[i] = new Model();
			m_ModelList[i]->SetId(id);
			m_ModelList[i]->LoadModel(path);
		}

		// Read 2D textures information
		fscanf(f, "\n#2D Textures: %d\n", &m_NTextures);
		m_TextureList = new Texture*[m_NTextures];
		for (int i = 0; i < m_NTextures; i++)
		{
			char path[LENGTH] = "../Resources/";
			int id;
			char file[LENGTH];
			char wrapping[LENGTH];
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "FILE %s", file);
			fscanf(f, "TILING %s", wrapping);
			strcat(path, file);
			m_TextureList[i] = new Texture();
			m_TextureList[i]->SetId(id);
			m_TextureList[i]->LoadTexture(path, GetWrappingMode(wrapping));
		}

		// Read cube textures information
		fscanf(f, "\n#Cube Textures: %d\n", &m_NTextures);

//		m_TextureList = new Texture*[m_NTextures];
//		for (int i = 0; i < m_NTextures; i++)
//		{
//			int id;
//			fscanf(f, "ID %d\n", &id);
//			const char ** filenames = new const char*[6];
//			for (int j = 0; j < 6; j++)
//			{
//				char path[LENGTH] = "../Resources/";
//				char file[LENGTH];
//				fscanf(f, "FILE %s\n", file);
//				strcat(path, file);
////				filenames[i] = path;
//			}
//			char wrapping[LENGTH];
//			fscanf(f, "TILING %s", wrapping);
//			m_TextureList[i] = new Texture();
//			m_TextureList[i]->SetId(id);
//			m_TextureList[i]->LoadTexture(filenames, GetWrappingMode(wrapping));
//		}

		// Read shaders information
		fscanf(f, "#Shaders: %d\n", &m_NShaders);
		m_ShaderList = new Shaders*[m_NShaders];
		for (int i = 0; i < m_NShaders; i++)
		{
			char path1[LENGTH] = "../Resources/";
			char path2[LENGTH] = "../Resources/";
			int id;
			char file1[LENGTH];
			char file2[LENGTH];
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "FILE %s\n", file1);
			fscanf(f, "FILE %s\n", file2);
			int nStates;
			fscanf(f, "STATES %d\n", &nStates);
			GLenum * states = new GLenum[nStates];
			for (int j = 0; j < nStates; j++)
			{
				char state[LENGTH];
				fscanf(f, "STATE %s", state);
				states[i] = GetShaderState(state);
			}
			strcat(path1, file1);
			strcat(path2, file2);
			m_ShaderList[i] = new Shaders();
			m_ShaderList[i]->SetId(id);
			int initStatus;
			initStatus = m_ShaderList[i]->Initialize(path1, path2);
			if (initStatus != 0)
			{
				return initStatus;
			}
			m_ShaderList[i]->SetNStates(nStates);
			m_ShaderList[i]->SetStates(states);
		}
	}
	else
	{
		printf("Error while opening file: %s\n", filename);
		return -3;
	}
	fclose(f);
	return 0;
}

GLenum ResourceManager::GetWrappingMode(const char* wrappingMode)
{
	if (strcmp(wrappingMode, "REPEAT") == 0)
	{
		return GL_REPEAT;
	}
	if (strcmp(wrappingMode, "CLAMP") == 0)
	{
		return GL_CLAMP_TO_EDGE;
	}
	return GL_MIRRORED_REPEAT;
}

GLenum ResourceManager::GetShaderState(const char* state)
{
	if (strcmp(state, "CULLING") == 0)
	{
		return GL_CULL_FACE;
	}
	if (strcmp(state, "ALPHA") == 0)
	{
		return GL_ALPHA;
	}
	return GL_DEPTH_TEST;
}
