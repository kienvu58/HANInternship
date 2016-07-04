#include "stdafx.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}

int Model::GetId() const
{
	return m_Id;
}

void Model::SetId(int id)
{
	m_Id = id;
}