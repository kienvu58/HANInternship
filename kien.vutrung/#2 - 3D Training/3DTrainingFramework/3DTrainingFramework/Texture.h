#pragma once
class Texture
{
public:
	Texture();
	~Texture();
	int GetId() const;
	void SetId(int id);
private:
	int m_Id;
};

