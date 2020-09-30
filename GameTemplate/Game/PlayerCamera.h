#pragma once
#include "Player.h"

class PlayerCamera : public IGameObject
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Update();
	bool Start();
	

	const CVector3& GetPosition() {
		return m_pos;
	}

	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}
	
private:
	CVector3 m_pos = { 0.0f, 200.0f, 300.0f };
	
	CVector3 old_pos = { 0.0f, 0.0f, 0.0f };

	CVector3 Camera_pos = { 0.0f, 0.0f, 0.0f };

	//ƒXƒLƒ“ƒ‚ƒfƒ‹
	SkinModel m_model;

private:
	Player* m_player = nullptr;

};

