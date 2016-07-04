#pragma once
#include "Object.h"
class Circle :
	public Object
{
public:
	Circle();
	Circle(float x, float y, float mass, float radius);
	void Render();
	Type GetType() const;
	float GetRadius() const;
	bool Contains(float x, float y);
	~Circle();
private:
	float m_fRadius;
};

