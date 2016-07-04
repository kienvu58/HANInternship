#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

int Object::GetId() const
{
	return m_Id;
}

void Object::SetId(int id)
{
	m_Id = id;
}
