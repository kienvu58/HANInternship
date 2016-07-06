#pragma once

#include "../Utilities/esUtil.h"
#include <vector>

class Shaders
{
public:
	Shaders();
	~Shaders();
	int GetId() const;
	void SetId(int id);
	int Initialize(char * fileVertexShader, char * fileFragmentShader);
	GLuint GetProgram() const;
	void SetStates(std::vector<GLenum> states);
	void EnableStates();
	void DisableStates();

	GLint iPosLoc;
	GLint iUVLoc;
	GLint iMVPLoc;
private:
	int m_Id;
	GLuint m_Program;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;
	std::vector<GLenum> m_States;
};

