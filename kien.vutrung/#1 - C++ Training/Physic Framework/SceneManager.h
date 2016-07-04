#pragma once

#include <vector>
#include "Object.h"
#include "Box.h"
#include "Plane.h"
#include "Circle.h"

using namespace std;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Render();
	void Update(float frameTime);
	void AddObject(Object * object);
	static SceneManager * GetInstance();
	vector<Object *>* GetObjectList();
	void PickObject(int x, int y);
	void DragObject(int x, int y);
	void ReleaseObject();
	void Init(const char * filename);
private:
	static SceneManager * s_Instance;
	vector<Object *> m_ObjectList;
	Object * m_PickedObject;
};

