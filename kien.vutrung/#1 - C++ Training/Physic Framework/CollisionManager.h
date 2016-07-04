#pragma once

#include <vector>
#include "Object.h"
#include "Circle.h"
#include "Box.h"
#include "Plane.h"
#include "SceneManager.h"
#include <cstdio>
using namespace std;
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void ResolveAllCollisions(float frameTime);
	void ResolveCollision(Object& obj1, Object& obj2);
	static CollisionManager * GetInstance();
	vec2 DetectCollision(const Object& obj1, const Object& obj2);
	vec2 DetectCollision(const Circle& circle, const Box& box);
	vec2 DetectCollision(const Box& box, const Circle& circle);
	vec2 DetectCollision(const Box& box1, const Box& box2);
	vec2 DetectCollision(const Circle& circle1, const Circle& circle2);
	vec2 DetectCollision(const Plane& plane, const Circle& circle);
	vec2 DetectCollision(const Plane& plane, const Box& box);
	vec2 DetectCollision(const Circle& circle, const Plane& plane);
	vec2 DetectCollision(const Box& box, const Plane& plane);
private:
	static CollisionManager * s_Instance;
	vector<Object *>* m_pObjectList;
};

