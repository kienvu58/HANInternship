#pragma once
#include "Object.h"

class SceneManager
{
public:
	~SceneManager();
	static SceneManager * GetInstance();
	void Initialize(const char * filename);
private:
	SceneManager();
	int m_NObjects;
	Object ** m_ObjectList;
	static SceneManager * s_Instance;
};

