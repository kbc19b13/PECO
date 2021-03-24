#pragma once
#include "Player.h"

class PlayerCamera : public IGameObject
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Update();
	bool Start();
	/// <summary>
	/// �J�����̍X�V����
	/// </summary>
	void CameraUpdate();

private:
	//��O�̃J�������W
	CVector3 old_pos = { 0.0f, 0.0f, 0.0f };
	//�J�����̍��W
	CVector3 Camera_pos = { 0.0f, 200.0f, 300.0f };

private:
	//�X�L�����f��
	SkinModel m_model;

private:
	Player* m_player = nullptr;

};

