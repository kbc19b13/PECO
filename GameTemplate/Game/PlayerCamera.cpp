#include "stdafx.h"
#include "PlayerCamera.h"

PlayerCamera::PlayerCamera()
{

}
PlayerCamera::~PlayerCamera()
{

}

bool PlayerCamera::Start()
{
	/// <summary>
	//////////const�ϐ���ݒ�////////////
	/// </summary>
	/// �ݒ� �� set
	/// 
	//�����ʂ�ݒ�
	const float set_far = 10000.0f;


	//Player�̃C���X�^���X���擾
	m_player = Player::P_GetInstance();

	
	g_camera3D.SetFar(set_far);
	
	return true;
}

void PlayerCamera::Update()
{
	/// <summary>
	//////////const�ϐ���ݒ�////////////
	/// </summary>
	/// �ݒ� �� set
	/// 
	const float set_height = 50.0f;

	
	CVector3 target = m_player->GetPosition();

	old_pos = Camera_pos;

	target.y += set_height;

	Camera_pos = target + m_DiagonalFixed;
	

	g_camera3D.SetTarget(target);
	g_camera3D.SetPosition(Camera_pos);
	
	//�J�����̍X�V�B
	g_camera3D.Update();
}

