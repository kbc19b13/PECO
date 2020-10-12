#include "stdafx.h"
#include "Player.h"
#include "..//mtEngine/mtGameTime.h"
//#include "..//mtEngine/mtStopwatch.h"


Player::Player()
{

	
}


Player::~Player()
{
	DeleteGO("Player");
}

bool Player::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/PECO.cmo");

	//AnimationClip�����[�h(tka�t�@�C���̓ǂݍ���)
	//Animaiton�̏��������s��
	m_PlayerAnimationClips[0].Load(L"Assets/animData/Walk_PECO.tka");
	m_PlayerAnimationClips[0].SetLoopFlag(true);
	m_PlayerAnimationClips[1].Load(L"Assets/animData/Sneak_PECO.tka");
	m_PlayerAnimationClips[1].SetLoopFlag(true);
	m_PlayerAnimationClips[2].Load(L"Assets/animData/Cat_PECO.tka");
	m_PlayerAnimationClips[2].SetLoopFlag(true);
	m_PlayerAnimationClips[3].Load(L"Assets/animData/Extraction_PECO.tka");
	m_PlayerAnimationClips[3].SetLoopFlag(true);
	//�A�j���[�V�����̏�����
	m_PlayerAnimation.Init(
		//�A�j���[�V�����𗬂��X�L�����f��(�֘A�t��)
		m_model,
		//�A�j���[�V�����N���b�v�̔z��
		m_PlayerAnimationClips,
		//�A�j���[�V�����N���b�v�̐�
		4
	);

	m_CCon.Init(30.0f, 160.0f, m_pos);
	
	return true;
}

void Player::Update()
{
	float frametime = GameTime().GetFrameDeltaTime();
	m_speed.x = g_pad[0].GetLStickXF() * -300.0f;
	m_speed.z = g_pad[0].GetLStickYF() * -300.0f;
	//m_speed.y -= 980.0f * frametime;

	
	m_pos = m_CCon.Execute(frametime, m_speed);

	
	m_PlayerAnimation.Play(0);
	
	if (g_pad[0].IsPress(enButtonB))
	{
		m_PlayerAnimation.Play(1);
	}

	/*if (g_pad[0].IsPress(enButtonLeft)) {
		m_pos.x += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_pos.x -= 5.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_pos.z += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_pos.z -= 5.0f;
	}*/

	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	
	//�A�j���[�V�����̍Đ�
	m_PlayerAnimation.Update(1.0f/30.0f);
	
	Draw();
}
void Player::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

//start
//update
/*
ondestroy


*/