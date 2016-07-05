#pragma once
#include <vector>
#include "Object.h"
#include "Camera.h"

enum Key { Forward, Backward, Left, Right, Up, Down, Reset, N_KEYS };
class WorldManager
{
public:
	~WorldManager();
	void Draw();
	static WorldManager * GetInstance();
	void AddObject(Object * pObject);
	void Update(float deltaTime);
	void SetKeyEvent(int keyNumber, bool isPressed);
	void SetMousePosition(int index, int x, int y);
private:
	std::vector<Object *> m_ObjectList;
	Camera m_Camera;
	static WorldManager * s_Instance;
	WorldManager();
	bool m_bIsPressed[N_KEYS];
	Vector2 m_vec2MousePosition[2];
	float m_fPitch;
	float m_fYaw;
};

