#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager * ResourceManager::s_Instance = nullptr;

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
