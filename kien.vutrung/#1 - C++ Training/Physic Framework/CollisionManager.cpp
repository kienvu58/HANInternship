#include "CollisionManager.h"
#include <algorithm>

CollisionManager * CollisionManager::s_Instance = nullptr;

CollisionManager::CollisionManager()
	: m_pObjectList(SceneManager::GetInstance()->GetObjectList())
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::ResolveAllCollisions(float frameTime)
{
	for (size_t i = 0; i < m_pObjectList->size() - 1; i++)
	{
		for (size_t j = i + 1; j < m_pObjectList->size(); j++)
		{
			ResolveCollision(*m_pObjectList->at(i), *m_pObjectList->at(j));
		}
	}
}

void CollisionManager::ResolveCollision(Object & obj1, Object & obj2)
{
	vec2 n = DetectCollision(obj1, obj2);
	if (isNull(n))
	{
		return;
	}
	if (obj2.GetType() == PLANE)
	{
		ResolveCollision(obj2, obj1);
		return;
	}
	vec2 orientation = obj2.GetCenter() - obj1.GetCenter();
	n *= (dot(n, orientation) > 0) ? 1 : -1;
	vec2 v1 = obj1.GetVelocity();
	vec2 v2 = obj2.GetVelocity();
	float m1 = obj1.GetMass();
	float m2 = obj2.GetMass();
	vec2 v12 = v1 - v2;
	float J = - ((1 + COR) * dot(v12, n)) / (dot(n, n) * (1/m1 + 1/m2));
	v1 += J / m1 * n;
	v2 += -J / m2 * n;
	if (obj1.GetType() != PLANE)
	{
		obj1.SetVelocity(v1);
	}
	obj2.SetVelocity(v2);
	obj2.SetPosition(obj2.GetPosition() + n);
}

CollisionManager * CollisionManager::GetInstance()
{
	if (!s_Instance)
	{
		s_Instance = new CollisionManager();
	}
	return s_Instance;
}

vec2 CollisionManager::DetectCollision(const Object & obj1, const Object & obj2)
{
	Type obj1Type = obj1.GetType();
	Type obj2Type = obj2.GetType();
	
	if (obj1Type == BOX && obj2Type == BOX)
	{
		return DetectCollision((Box &)obj1, (Box &)obj2);
	}
	if (obj1Type == BOX && obj2Type == CIRCLE)
	{
		return DetectCollision((Box &)obj1, (Circle &)obj2);
	}
	if (obj1Type == CIRCLE && obj2Type == BOX)
	{
		return DetectCollision((Circle &)obj1, (Box &)obj2);
	}
	if (obj1Type == CIRCLE && obj2Type == CIRCLE)
	{
		return DetectCollision((Circle &)obj1, (Circle &)obj2);
	}
	if (obj1Type == PLANE && obj2Type == BOX)
	{
		return DetectCollision((Plane &)obj1, (Box &)obj2);
	}
	if (obj1Type == BOX && obj2Type == PLANE)
	{
		return DetectCollision((Box &)obj1, (Plane &)obj2);
	}
	if (obj1Type == CIRCLE && obj2Type == PLANE)
	{
		return DetectCollision((Circle &)obj1, (Plane &)obj2);
	}
	if (obj1Type == PLANE && obj2Type == CIRCLE)
	{
		return DetectCollision((Plane &)obj1, (Circle &)obj2);
	}
	return vec2();
}

vec2 CollisionManager::DetectCollision(const Circle & circle, const Box & box)
{
	return DetectCollision(box, circle);
}

vec2 CollisionManager::DetectCollision(const Box & box, const Circle & circle)
{
	vec2 * axes = new vec2[3];
	vec2 * vertices = box.GetVertices();
	float radius = circle.GetRadius();
	axes[0] = box.GetWidthVector();
	axes[1] = box.GetHeightVector();
	axes[2] = circle.GetPosition() - box.GetClosestVertice(circle.GetPosition());
	float displacement[3] = {};
	for (int i = 0; i < 3; i++)
	{
		if (isNull(axes[i]))
		{
			displacement[i] = 999999;
			continue;
		}
		float projLength[4];
		float projCenterLength = length(project(circle.GetPosition(), axes[i]));
		for (int j = 0; j < 4; j++)
		{
			projLength[j] = length(project(vertices[j], axes[i]));
		}
		float min = *min_element(projLength, projLength + 4);
		float max = *max_element(projLength, projLength + 4);
		//printf("%d %f %f %f\n", i, min, max, projCenterLength);
		if (projCenterLength >= min && (projCenterLength - radius) < max)
		{
			displacement[i] = (max - (projCenterLength - radius)) <
				(projCenterLength + radius - min) ?
				(max - (projCenterLength - radius)) :
				(min - projCenterLength - radius);
			//printf("%d 1\n", i);
		}
		if (projCenterLength <= min && (projCenterLength + radius) > min)
		{
			displacement[i] = min - projCenterLength - radius;
			//printf("%d 2\n", i);
		}
	}
	int minIndex = 0;
	for (int j = 1; j < 3; j++)
	{
		if (abs(displacement[j]) < abs(displacement[minIndex]))
		{
			minIndex = j;
		}
	}
	//printf("%f %f %f\n", displacement[0], displacement[1], displacement[2]);
	vec2 result = displacement[minIndex] * normalize(axes[minIndex]);
	if (!isNull(result))
	{
		printf("Collision\n");
	}
	delete[] vertices;
	delete[] axes;
	return result;
}

vec2 CollisionManager::DetectCollision(const Box & box1, const Box & box2)
{
	vec2 * vertices1 = box1.GetVertices();
	vec2 * vertices2 = box2.GetVertices();
	vec2 * axes = new vec2[4];
	float displacement[4] = {};
	axes[0] = box1.GetWidthVector();
	axes[1] = box1.GetHeightVector();
	axes[2] = box2.GetWidthVector();
	axes[3] = box2.GetHeightVector();

	for (int i = 0; i < 4; i++)
	{
		float dotProducts1[4];
		float dotProducts2[4];
		for (int j = 0; j < 4; j++)
		{
			dotProducts1[j] = dot(vertices1[j], axes[i]);
			dotProducts2[j] = dot(vertices2[j], axes[i]);
		}
		float min1 = *min_element(dotProducts1, dotProducts1 + 4);
		float max1 = *max_element(dotProducts1, dotProducts1 + 4);
		float min2 = *min_element(dotProducts2, dotProducts2 + 4);
		float max2 = *max_element(dotProducts2, dotProducts2 + 4);

		if (min1 <= min2 && min2 < max1)
		{
			displacement[i] = ((max1 - min2) < (max2 - min1)) ? (max1 - min2) : (min1 - max2);
		}
		if (min2 <= min1 && min1 < max2)
		{
			displacement[i] = ((max2 - min1) < (max1 - min2)) ? (min1 - max2) : (max1 - min2);
		}
	}
	int minIndex = 0;
	for (int j = 1; j < 4; j++)
	{
		if (abs(displacement[j]) < abs(displacement[minIndex]))
		{
			minIndex = j;
		}
	}
	vec2 result = displacement[minIndex] * axes[minIndex] / length2(axes[minIndex]);
	if (!isNull(result))
	{
		printf("Collision\n");
	}
	delete[] axes;
	delete[] vertices1;
	delete[] vertices2;
	return result;
}

vec2 CollisionManager::DetectCollision(const Circle & circle1, const Circle & circle2)
{
	vec2 axis = circle2.GetPosition() - circle1.GetPosition();
	vec2 projection1 = project(circle1.GetPosition(), axis);
	vec2 projection2 = project(circle2.GetPosition(), axis);
	float displacement = 0;
	float projLength1 = length(projection1);
	float projLength2 = length(projection2);
	if (projLength1 < projLength2 && 
		(projLength1 + circle1.GetRadius()) > (projLength2 - circle2.GetRadius()))
	{
		displacement = (projLength1 + circle1.GetRadius()) - (projLength2 - circle2.GetRadius());
	}
	if (projLength2 < projLength1 &&
		(projLength2 + circle1.GetRadius()) > (projLength1 - circle2.GetRadius()))
	{
		displacement = -(projLength2 + circle1.GetRadius()) + (projLength1 - circle2.GetRadius());
	}
	vec2 result = displacement * normalize(axis);
	if (!isNull(result))
	{
		printf("Collision\n");
	}
	return result;
}

vec2 CollisionManager::DetectCollision(const Plane & plane, const Circle & circle)
{
	vec2 axes[4] = { vec2(0, 1), vec2(-1, 0), vec2(0, -1), vec2(1, 0) };
	Role role = plane.GetRole();
	float radius = circle.GetRadius();
	float planeProjLength = length(project(plane.GetPosition(), axes[role]));
	float circleProjLength = length(project(circle.GetPosition(), axes[role]));
	vec2 result;
	if ((circleProjLength - radius) < planeProjLength && (role == 0 || role == 3))
	{
		result = (planeProjLength - (circleProjLength - radius)) * axes[role];
	}
	if ((circleProjLength + radius) > planeProjLength && (role == 1 || role == 2))
	{
		result = (planeProjLength - (circleProjLength + radius)) * axes[role];
	}
	if (!isNull(result))
	{
		printf("Plane collision %d %f %f\n", role, result.x, result.y);
	}
	return result;
}

vec2 CollisionManager::DetectCollision(const Plane & plane, const Box & box)
{
	vec2 axes[4] = { vec2(0, 1), vec2(-1, 0), vec2(0, -1), vec2(1, 0) };
	Role role = plane.GetRole();
	vec2 * vertices = box.GetVertices();
	float planeProjLength = length(project(plane.GetPosition(), axes[role]));
	float verticesProjectLength[4];
	for (int i = 0; i < 4; i++)
	{
		verticesProjectLength[i] = length(project(vertices[i], axes[role]));
	}
	float centerProjLength = length(project(box.GetCenter(), axes[role]));
	float max = *max_element(verticesProjectLength, verticesProjectLength + 4);
	float delta = max - centerProjLength;
	float min = max - 2 * delta;
	vec2 result;
	
	if (max >= planeProjLength && (role == 1 || role == 2))
	{
		result = (max - planeProjLength) * axes[role];
	}
	if (min <= 0 && (role == 0 || role == 3))
	{
		result = (min - planeProjLength) * axes[role];
	}
	if (!isNull(result))
	{
		printf("Plane collision %d %f %f\n", role, result.x, result.y);
	}
	return result;
}

vec2 CollisionManager::DetectCollision(const Circle & circle, const Plane & plane)
{
	return DetectCollision(plane, circle);
}

vec2 CollisionManager::DetectCollision(const Box & box, const Plane & plane)
{
	return DetectCollision(plane, box);
}
