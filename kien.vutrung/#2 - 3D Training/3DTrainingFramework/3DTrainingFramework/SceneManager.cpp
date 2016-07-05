#include "stdafx.h"
#include "SceneManager.h"

SceneManager* SceneManager::s_Instance = nullptr;

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

void SceneManager::Initialize(const char* filename)
{
	FILE* f = fopen(filename, "r");
	if (f)
	{
		fscanf(f, "#Objects: %d\n", &m_NObjects);
		m_ObjectList = new Object*[m_NObjects];
		for (int i = 0; i < m_NObjects; i++)
		{
			m_ObjectList[i] = new Object();
			int id, modelId;
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "MODEL %d", &modelId);
			int nTextures;
			fscanf(f, "TEXTURES %d\n", &nTextures);
			int* textureIds = new int[nTextures];
			for (int j = 0; j < nTextures; j++)
			{
				fscanf(f, "TEXTURE %d\n", &textureIds[j]);
			}
			int nCubeTextures;
			fscanf(f, "CUBETEXTURES %d\n", &nCubeTextures);
			int* cubeTextureIds = new int[nCubeTextures];
			for (int j = 0; j < nTextures; j++)
			{
				fscanf(f, "CUBETEXTURE %d\n", &cubeTextureIds[j]);
			}
			Vector3 pos, rot, scale;
			fscanf(f, "POSITION %f, %f, %f\n", &pos.x, &pos.y, &pos.z);
			fscanf(f, "ROTATION %f, %f, %f\n", &rot.x, &rot.y, &rot.z);
			fscanf(f, "SCALE %f, %f, %f\n", &scale.x, &scale.y, &scale.z);
			m_ObjectList[i]->SetId(id);
			m_ObjectList[i]->SetModelId(modelId);
			if (nTextures)
			{
				m_ObjectList[i]->SetNTextures(nTextures);
				m_ObjectList[i]->SetTextureIds(textureIds);
			}
			else
			{
				m_ObjectList[i]->SetNTextures(nCubeTextures);
				m_ObjectList[i]->SetTextureIds(cubeTextureIds);
			}
			m_ObjectList[i]->SetPosition(pos);
			m_ObjectList[i]->SetRotation(rot);
			m_ObjectList[i]->SetScale(scale);
		}
	}
	else
	{
		printf("Error while opening file: %s\n", filename);
	}
}
