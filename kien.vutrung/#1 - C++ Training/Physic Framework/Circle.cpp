#include "Circle.h"


Circle::Circle()
{
}

Circle::Circle(float x, float y, float mass, float radius)
	: Object(x, y, mass), m_fRadius(radius)
{
}

void Circle::Render()
{
	VideoDriver::GetInstance()->DrawCircle(m_vecPosition, m_fRadius);
	if (m_bIsDraggable)
	{
		VideoDriver::GetInstance()->DrawLine(GetCenter(), m_vecTarget);
	}
}


Type Circle::GetType() const
{
	return CIRCLE;
}

float Circle::GetRadius() const
{
	return m_fRadius;
}

bool Circle::Contains(float x, float y)
{
	vec2 point(x, y);
	return length(m_vecPosition - point) <= m_fRadius;
}


Circle::~Circle()
{
}
