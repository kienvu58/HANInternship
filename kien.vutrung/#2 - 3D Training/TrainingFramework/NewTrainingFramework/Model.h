#pragma once
#include "../Utilities/esUtil.h"

class Model
{
public:
	explicit Model(const char* filename);
	~Model();
	GLuint GetVboId() const;
	GLuint GetIboId() const;
	int GetNIndices() const;
	int GetNVertices() const;
private:
	int m_NIndices;
	int m_NVertices;
	GLuint m_VboId;
	GLuint m_IboId;
};

