#include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
}

int Texture::GetId() const
{
	return m_Id;
}

void Texture::SetId(int id)
{
	m_Id = id;
}
