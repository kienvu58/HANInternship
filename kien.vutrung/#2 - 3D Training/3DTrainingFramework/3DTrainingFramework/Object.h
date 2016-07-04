#pragma once
class Object
{
public:
	Object();
	~Object();
	int GetId() const;
	void SetId(int id);
private:
	int m_Id;
};

