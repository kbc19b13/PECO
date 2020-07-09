#pragma once
#include "character/CharacterController.h"

class Player
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
private:
	SkinModel m_model;									//スキンモデル。

	CVector3 m_pos = { 0.0f, 0.0f, 0.0f };
};

