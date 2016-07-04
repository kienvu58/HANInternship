#pragma once
class ResourceManager
{
public:
	~ResourceManager();
	static ResourceManager * GetInstance();
private:
	ResourceManager();
	static ResourceManager * s_Instance;
};

