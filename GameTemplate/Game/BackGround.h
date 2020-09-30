#pragma once
#include "../mtEngine/mtGameObject.h"
#include "character/CharacterController.h"
#include "level/Level.h"

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Draw();

	const CVector3& GetPosition() {
		return m_pos;
	}

	void SetPosition(const CVector3 pos)
	{
		m_pos = pos;
	}

private:
	SkinModel m_model;

	//ƒŒƒxƒ‹
	Level m_level;

	CVector3 m_pos = { 0.0f, 0.0f, 0.0f };
};

