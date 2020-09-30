#pragma once
class Mori : public IGameObject
{
public:
	Mori();
	~Mori();

private:

	CVector3 m_pos = { 0.0f, 0.0f, 0.0f };

};

