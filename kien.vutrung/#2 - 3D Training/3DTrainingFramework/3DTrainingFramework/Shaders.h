#pragma once
class Shaders
{
public:
	Shaders();
	~Shaders();
	int GetId() const;
	void SetId(int id);
private:
	int m_Id;
};

