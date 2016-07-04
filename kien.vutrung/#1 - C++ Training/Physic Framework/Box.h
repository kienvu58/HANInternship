#pragma once
#include "Object.h"

class Box :
	public Object
{
public:
	Box();
	Box(float x, float y, float mass, float width, float height);
	void Render();
	Type GetType() const;
	~Box();
	vec2 * GetVertices() const;
	const vec2 & GetWidthVector() const;
	const vec2 & GetHeightVector() const;
	vec2 GetClosestVertice(const vec2& point) const;
	vec2 GetCenter() const;
	bool Contains(float x, float y);
private:
	vec2 m_vecWidth;
	vec2 m_vecHeight;
};

