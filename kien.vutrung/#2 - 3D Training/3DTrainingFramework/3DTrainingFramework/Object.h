#pragma once
#include "../Utilities/Math.h"

class Object
{
public:
	Object();
	~Object();
	int GetId() const;
	void SetId(int id);
	void SetModelId(int modelId);
	void SetTextureIds(int* textureIds);
	void SetShaderId(int shaderId);
	void SetPosition(Vector3& position);
	void SetRotation(Vector3& rotation);
	void SetScale(Vector3& scale);
	int GetNTextures() const;
	void SetNTextures(int nTextures);
	Matrix GetMatModel() const;
private:
	int m_Id;
	int m_ModelId;
	int m_NTextures;
	int * m_TextureIds;
	int m_ShaderId;
	Vector3 m_Position;
	Vector3 m_Rotation;
	Vector3 m_Scale;
	Matrix m_matModel;
};

