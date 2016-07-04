#include "stdafx.h"
#include "WorldManager.h"

WorldManager* WorldManager::s_Instance = nullptr;

WorldManager::WorldManager(): m_fPitch(0), m_fYaw(0)
{
	for (int i = 0; i < N_KEYS; i++)
	{
		m_bIsPressed[i] = false;
	}
	m_vec2MousePosition[0] = m_vec2MousePosition[1] = Vector2();
}


WorldManager::~WorldManager()
{
	for (auto it : m_ObjectList)
	{
		delete it;
	}
	m_ObjectList.clear();
}

void WorldManager::Draw()
{
	for (auto it : m_ObjectList)
	{
		it->Draw();
	}
}

WorldManager* WorldManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new WorldManager();
	}
	return s_Instance;
}

void WorldManager::AddObject(Object* pObject)
{
	m_ObjectList.push_back(pObject);
}

void WorldManager::Update(float deltaTime)
{
	if (m_bIsPressed[Reset])
	{
		m_Camera = Camera();
	}
	Vector3 moveDirection(m_bIsPressed[Right] - m_bIsPressed[Left],
	                      m_bIsPressed[Up] - m_bIsPressed[Down],
	                      m_bIsPressed[Backward] - m_bIsPressed[Forward]);
	m_Camera.Move(moveDirection, deltaTime);
	Vector2 delta = m_vec2MousePosition[1] - m_vec2MousePosition[0];
	m_vec2MousePosition[0] = m_vec2MousePosition[1];
	float sensitivity = 0.5f;
	m_fPitch -= delta.y * sensitivity;
	m_fYaw += delta.x * sensitivity;
	m_fPitch = m_fPitch < 89.0f ? m_fPitch : 89.0f;
	m_fPitch = m_fPitch > -89.0f ? m_fPitch : -89.0f;
	m_Camera.Rotate(Radians(m_fPitch), Radians(m_fYaw));
	m_Camera.UpdateViewMatrix();
	for (auto it : m_ObjectList)
	{
		it->SetViewMatrix(m_Camera.GetViewMatrix());
	}
}

void WorldManager::SetKeyEvent(int keyNumber, bool isPressed)
{
	m_bIsPressed[keyNumber] = isPressed;
}

void WorldManager::SetMousePosition(int index, int x, int y)
{
	m_vec2MousePosition[index] = Vector2(x, y);
}
