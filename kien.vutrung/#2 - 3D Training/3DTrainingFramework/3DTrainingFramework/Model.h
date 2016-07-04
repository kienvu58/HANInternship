#pragma once
class Model
{
public:
	Model();
	~Model();
	int GetId() const;
	void SetId(int id);
private:
	int m_Id;
};

