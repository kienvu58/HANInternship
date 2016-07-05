#pragma once

#define MAX_LENGTH	260
#include "../Utilities/esUtil.h"

class Shaders
{
public:
	Shaders();
	~Shaders();
	int GetId() const;
	void SetId(int id);
	int Initialize(char * fileVertexShader, char * fileFragmentShader);
	GLuint GetProgram() const;
	void SetStates(GLenum* states);
	int GetNStates() const;
	void SetNStates(int nStates);
private:
	int m_Id;
	GLuint m_Program;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	int m_NStates;
	GLenum * m_States;
};

