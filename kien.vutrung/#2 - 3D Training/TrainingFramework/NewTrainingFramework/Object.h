#pragma once
#include "Model.h"
#include "../Utilities/Math.h"
#include "Texture.h"
#include "Shaders.h"


class Object
{
public:
	Object(Model * pModel, Texture * pTexture, Shaders * pShader, Matrix matModel, Matrix matView, Matrix matProjection);
	~Object();
	void Draw();
	void SetModelMatrix(Matrix matModel);
	void SetViewMatrix(Matrix matView);
	void SetProjectionMatrix(Matrix matProjection);
	Matrix GetMVPMatrix();
private:
	Model * m_pModel;
	Texture * m_pTexture;
	Shaders * m_pShader;
	Matrix m_matModel;
	Matrix m_matView;
	Matrix m_matProjection;
};

