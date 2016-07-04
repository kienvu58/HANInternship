#include "stdafx.h"
#include "SceneManager.h"

SceneManager * SceneManager::s_Instance = nullptr;

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
