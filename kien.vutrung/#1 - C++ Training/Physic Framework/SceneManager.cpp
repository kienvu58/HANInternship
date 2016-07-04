#include "SceneManager.h"

SceneManager * SceneManager::s_Instance = nullptr;

SceneManager::SceneManager()
	: m_PickedObject(nullptr)
{
	Plane * top = new Plane(TOP);
	Plane * left = new Plane(LEFT);
	Plane * bottom = new Plane(BOTTOM);
	Plane * right = new Plane(RIGHT);
	m_ObjectList.push_back(top);
	m_ObjectList.push_back(left);
	m_ObjectList.push_back(bottom);
	m_ObjectList.push_back(right);
}


SceneManager::~SceneManager()
{
	for (auto it : m_ObjectList)
	{
		it->~Object();
	}
	m_ObjectList.clear();
}

void SceneManager::Render()
{
	for (auto it : m_ObjectList)
	{
		it->Render();
	}
}

void SceneManager::Update(float frameTime)
{
	for (auto it : m_ObjectList)
	{
		it->Update(frameTime);
	}
}

void SceneManager::AddObject(Object * object)
{
	m_ObjectList.push_back(object);
}

SceneManager * SceneManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new SceneManager();
	}
	return s_Instance;
}

vector<Object*>* SceneManager::GetObjectList()
{
	return &m_ObjectList;
}

void SceneManager::PickObject(int x, int y)
{
	for (auto it : m_ObjectList)
	{
		if (it->Contains(x, y))
		{
			it->SetDraggable(true);
			m_PickedObject = it;
			return;
		}
	}
}

void SceneManager::DragObject(int x, int y)
{
	if (m_PickedObject)
	{
		m_PickedObject->MoveTo(x, y);
	}
}

void SceneManager::ReleaseObject()
{
	if (m_PickedObject)
	{
		m_PickedObject->SetDraggable(false);
		m_PickedObject = nullptr;
	}
}

void SceneManager::Init(const char * filename)
{
	const int BUFFER_LENGTH = 80;
	const int MAX_OBJECT_TYPE_LENGTH = 10;
	FILE * f;
	char line[BUFFER_LENGTH];
	fopen_s(&f, filename, "r");
	if (!f)
	{
		printf("Could not open file %s\n", filename);
		return;
	}

	while (fgets(line, BUFFER_LENGTH, f))
	{
		if (strcmp(line, "TYPE") > 0)
		{
			char c_objType[MAX_OBJECT_TYPE_LENGTH];
			sscanf(line, "TYPE: %s", c_objType);

			Object * newObj;

			if (strcmp(c_objType, "CIRCLE") == 0)
			{
				;
				float x, y, mass, radius;

				fgets(line, BUFFER_LENGTH, f);
				sscanf(line, "POSITION: %f, %f, %f", &x, &y, &radius);

				fgets(line, BUFFER_LENGTH, f);
				sscanf(line, "MASS: %f", &mass);
				newObj = new Circle(x, y, mass, radius);
			}

			if (strcmp(c_objType, "BOX") == 0)
			{
				float x, y, mass, width, height;

				fgets(line, BUFFER_LENGTH, f);
				sscanf(line, "POSITION: %f, %f, %f, %f", &x, &y, &width, &height);

				fgets(line, BUFFER_LENGTH, f);
				sscanf(line, "MASS: %f", &mass);
				newObj = new Box(x, y, mass, width, height);
			}

			AddObject(newObj);
		}
	}
	std::fclose(f);
}
