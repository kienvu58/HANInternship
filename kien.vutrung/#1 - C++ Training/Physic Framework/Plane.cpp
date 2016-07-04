#include "Plane.h"



Plane::Plane()
{
}

Plane::Plane(float x, float y, Role role)
	: Object(x, y, 0), m_Role(role)
{
}

Plane::Plane(Role role)
	: m_Role(role)
{
	switch (m_Role)
	{
	case TOP:
		m_vecPosition = vec2(0, 0);
		break;
	case LEFT:
		m_vecPosition = vec2(SCREEN_W, 0);
		break;
	case BOTTOM:
		m_vecPosition = vec2(SCREEN_W, SCREEN_H - 1);
		break;
	case RIGHT:
		m_vecPosition = vec2(0, SCREEN_H - 1);
		break;
	default:
		break;
	}
}

void Plane::Render()
{
	vec2 start, end;
	switch (m_Role)
	{
	case TOP:
	case BOTTOM:
		start = vec2(0, m_vecPosition.y);
		end = vec2(SCREEN_W, m_vecPosition.y);
		break;
	case LEFT:
	case RIGHT:
		start = vec2(m_vecPosition.x, 0);
		end = vec2(m_vecPosition.x, SCREEN_H);
		break;
	default:
		break;
	}
	VideoDriver::GetInstance()->DrawLine(start, end);
}


void Plane::Update(float frameTime)
{
}

Type Plane::GetType() const
{
	return PLANE;
}

Role Plane::GetRole() const
{
	return m_Role;
}

Plane::~Plane()
{
}
