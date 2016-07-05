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

void Object::SetModelId(int modelId)
{
	m_ModelId = modelId;
}

void Object::SetTextureIds(int* textureIds)
{
	m_TextureIds = textureIds;
}

void Object::SetShaderId(int shaderId)
{
	m_ShaderId = shaderId;
}

void Object::SetPosition( Vector3& position)
{
	m_Position = position;
}

void Object::SetRotation(Vector3& rotation)
{
	m_Rotation = rotation;
}

void Object::SetScale(Vector3& scale)
{
	m_Scale = scale;
}

int Object::GetNTextures() const
{
	return m_NTextures;
}

void Object::SetNTextures(int nTextures)
{
	m_NTextures = nTextures;
}

Matrix Object::GetMatModel() const
{
	return m_matModel;
}
