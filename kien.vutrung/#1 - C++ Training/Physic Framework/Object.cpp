#include "Object.h"


Object::Object()
{
}

Object::Object(float x, float y, float mass)
	: m_vecPosition(vec2(x, y)), m_fMass(mass), m_bIsDraggable(false)
{
}

void Object::Render()
{
}


void Object::Update(float frameTime)
{
	vec2 force = vec2(0, 0);
	if (!m_bIsDraggable)
	{
		m_vecTarget = GetCenter();
		vec2 g = vec2(0, 9.81);
		force += m_fMass * g;
	}
	m_vecPosition += m_vecVelocity * frameTime + 0.5f * m_vecAcceleration * frameTime * frameTime;
	vec2 newAcceleration = force / m_fMass;
	vec2 averageAcceleration = 0.5f * (newAcceleration + m_vecAcceleration);
	m_vecVelocity += averageAcceleration * frameTime;
}

Object::~Object()
{
}

Type Object::GetType() const
{
	return OBJECT;
}

void Object::SetVelocity(vec2 velocity)
{
	m_vecVelocity = velocity;
}

void Object::SetPosition(vec2 position)
{
	m_vecPosition = position;
}

void Object::SetAcceleration(vec2 acceleration)
{
	m_vecAcceleration = acceleration;
}

vec2 Object::GetVelocity() const
{
	return m_vecVelocity;
}

vec2 Object::GetPosition() const
{
	return m_vecPosition;
}

float Object::GetMass() const
{
	return m_fMass;
}

vec2 Object::GetCenter() const
{
	return m_vecPosition;
}

bool Object::Contains(float x, float y)
{
	return false;
}

void Object::SetDraggable(bool isDraggable)
{
	m_bIsDraggable = isDraggable;
}


void Object::MoveTo(float x, float y)
{
	m_vecTarget = vec2(x, y);
	m_vecVelocity = m_vecTarget - GetCenter();
}
