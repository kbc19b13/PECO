#pragma once
#include "../mtEngine/mtGameObject.h"
#include "character/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
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

	CVector3 m_pos = { 5000.0f, 0.0f, -5000.0f };

};

