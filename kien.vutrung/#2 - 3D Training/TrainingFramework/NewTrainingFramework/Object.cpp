#include "stdafx.h"
#include "Object.h"
#include "Vertex.h"


Object::Object(Model * pModel, Texture * pTexture, Shaders * pShader, Matrix matModel, Matrix matView, Matrix matProjection)
	: m_pModel(pModel), m_pTexture(pTexture), m_pShader(pShader), m_matModel(matModel), m_matView(matView), m_matProjection(matProjection)
{
}

Object::~Object()
{
	delete m_pModel;
	delete m_pTexture;
}

void Object::Draw()
{
	glUseProgram(m_pShader->program);

	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIboId());
	glBindTexture(m_pTexture->GetTarget(), m_pTexture->GetTextureId());

	auto iTextureLoc = glGetUniformLocation(m_pShader->program, "u_texture");
	if (iTextureLoc != -1)
	{
		glUniform1i(iTextureLoc, 0);
	}

	if (m_pShader->iPosLoc != -1)
	{
		glEnableVertexAttribArray(m_pShader->iPosLoc);
		glVertexAttribPointer(m_pShader->iPosLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(POS_OFFSET));
	}

	if (m_pShader->iUVLoc != -1)
	{
		glEnableVertexAttribArray(m_pShader->iUVLoc);
		glVertexAttribPointer(m_pShader->iUVLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(UV_OFFSET));
	}

	if (m_pShader->iMVPLoc != -1)
	{
		glUniformMatrix4fv(m_pShader->iMVPLoc, 1, GL_FALSE, GetMVPMatrix().m[0]);
	}

	glDrawElements(GL_TRIANGLES, m_pModel->GetNIndices(), GL_UNSIGNED_INT, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::SetModelMatrix(Matrix model)
{
	m_matModel = model;
}

void Object::SetViewMatrix(Matrix view)
{
	m_matView = view;
}

void Object::SetProjectionMatrix(Matrix projection)
{
	m_matProjection = projection;
}

Matrix Object::GetMVPMatrix()
{
	return m_matModel * m_matView * m_matProjection;
}
