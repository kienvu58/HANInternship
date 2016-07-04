#pragma once
class SceneManager
{
public:
	~SceneManager();
	static SceneManager * GetInstance();
private:
	SceneManager();
	static SceneManager * s_Instance;
};

