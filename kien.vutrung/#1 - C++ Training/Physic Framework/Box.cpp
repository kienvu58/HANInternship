#include "Box.h"



Box::Box()
{
}

Box::Box(float x, float y, float mass, float width, float height)
	: Object(x, y, mass), m_vecWidth(vec2(width, 0)),
	m_vecHeight(vec2(0, height))
{
}

void Box::Render()
{
	VideoDriver::GetInstance()->DrawRect(m_vecPosition, m_vecWidth, m_vecHeight);
	if (m_bIsDraggable)
	{
		VideoDriver::GetInstance()->DrawLine(GetCenter(), m_vecTarget);
	}
}

Type Box::GetType() const
{
	return BOX;
}


Box::~Box()
{
}

vec2 * Box::GetVertices() const
{
	vec2 * vertices = new vec2[4];
	vertices[0] = m_vecPosition;
	vertices[1] = m_vecPosition + m_vecWidth;
	vertices[2] = m_vecPosition + m_vecWidth + m_vecHeight;
	vertices[3] = m_vecPosition + m_vecHeight;
	return vertices;
}

const vec2 & Box::GetWidthVector() const
{
	return m_vecWidth;
}

const vec2 & Box::GetHeightVector() const
{
	return m_vecHeight;
}

vec2 Box::GetClosestVertice(const vec2 & point) const
{
	vec2 * vertices = GetVertices();
	float distances[4] = {};
	for (int i = 0; i < 4; i++) {
		distances[i] = length(vertices[i] - point);
	}
	int minIndex = 0;
	for (int i = 1; i < 4; i++) {
		if (distances[i] < distances[minIndex])
		{
			minIndex = i;
		}
	}
	vec2 result = vec2(vertices[minIndex]);
	delete[] vertices;
	return result;
}

vec2 Box::GetCenter() const
{
	vec2 diagonal = m_vecWidth + m_vecHeight;
	vec2 midPoint = m_vecPosition + diagonal * 0.5f;
	return midPoint;
}

bool Box::Contains(float x, float y)
{
	float thisX = m_vecPosition.x;
	float thisY = m_vecPosition.y;
	return (x >= thisX && x <= thisX + m_vecWidth.x)
		&& (y >= thisY && y <= thisY + m_vecHeight.y);
}
