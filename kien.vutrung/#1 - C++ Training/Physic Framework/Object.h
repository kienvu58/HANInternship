#pragma once

#include "glmath.h"
#include "videoDriver.h"

#define COR 1.0f

enum Type {OBJECT, BOX, CIRCLE, PLANE};

class Object
{
public:
	Object();
	Object(float x, float y, float mass);
	virtual void Render();
	void Update(float frameTime);
	virtual ~Object();
	virtual Type GetType() const;
	void SetVelocity(vec2 velocity);
	void SetPosition(vec2 position);
	void SetAcceleration(vec2 acceleration);
	vec2 GetVelocity() const;
	vec2 GetPosition() const;
	float GetMass() const;
	virtual vec2 GetCenter() const;
	virtual bool Contains(float x, float y);
	void SetDraggable(bool isDraggable);
	void MoveTo(float x, float y);
protected:
	vec2 m_vecTarget;
	bool m_bIsDraggable;
	float m_fMass;
	vec2 m_vecPosition;
	vec2 m_vecVelocity;
	vec2 m_vecAcceleration;
	float m_fRotationAngle;
	float m_fAngularVelocity;
	float m_fAngularAcceleration;
};

