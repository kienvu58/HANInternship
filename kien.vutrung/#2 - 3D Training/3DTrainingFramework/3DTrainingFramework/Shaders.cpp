#include "stdafx.h"
#include "Shaders.h"


Shaders::Shaders(): m_States(nullptr)
{
}


Shaders::~Shaders()
{
	if (m_States)
	{
		delete m_States;
	}
	glDeleteProgram(m_Program);
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
}

int Shaders::GetId() const
{
	return m_Id;
}

void Shaders::SetId(int id)
{
	m_Id = id;
}

int Shaders::Initialize(char* fileVertexShader, char* fileFragmentShader)
{
	m_VertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);
	if (m_VertexShader == 0)
	{
		return -1;
	}

	m_FragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);
	if (m_FragmentShader == 0)
	{
		return -2;
	}

	m_Program = esLoadProgram(m_VertexShader, m_FragmentShader);
	return 0;
}

GLuint Shaders::GetProgram() const
{
	return m_Program;
}

void Shaders::SetStates(GLenum* states)
{
	m_States = states;
}

int Shaders::GetNStates() const
{
	return m_NStates;
}

void Shaders::SetNStates(int nStates)
{
	m_NStates = nStates;
}
