#pragma once
#include "../mtEngine/mtGameObject.h"
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();
	void Draw();

	const CVector3& GetPosition(){
		return m_pos;
	}

	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}

private:
	SkinModel m_model;									//スキンモデル。

	CharacterController CCon;

	CVector3 m_pos = { 2500.0f, 0.0f, -2500.0f };
	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };

};

