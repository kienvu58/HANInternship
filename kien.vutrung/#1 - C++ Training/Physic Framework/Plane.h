#pragma once
#include "Object.h"
#include "define.h"

enum Role { TOP, LEFT, BOTTOM, RIGHT };
class Plane :
	public Object
{
public:
	Plane();
	Plane(float x, float y, Role role);
	Plane(Role role);
	void Render();
	void Update(float frameTime);
	Type GetType() const;
	Role GetRole() const;
	~Plane();
private:
	Role m_Role;
};

