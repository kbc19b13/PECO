#include "stdafx.h"
#include "Player.h"
#include "..//mtEngine/mtGameTime.h"
//#include "..//mtEngine/mtStopwatch.h"

//�O���[�o����Player�͈�l����
Player* Player::m_instance = nullptr;

Player::Player()
{
	//�C���X�^���X�̐���
	if (m_instance != nullptr)
	{
		//2�̖ڂ���̓G���[���o��
		std::abort();
	}
	
	//Player���Œ�
	m_instance = this;
}


Player::~Player()
{
	DeleteGO("Player");
}

bool Player::Start()
{
	const float CCon_radius = 30.0f;
	const float height = 160.0f;


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

	

	m_CCon.Init(CCon_radius, height, m_pos);
	
	return true;
}

void Player::Update()
{
	const float playerSpeed = -300.0f;
	const float gravity = 980.0f;

	float frametime = GameTime().GetFrameDeltaTime();
	m_speed.x = g_pad[0].GetLStickXF() * playerSpeed;
	m_speed.z = g_pad[0].GetLStickYF() * playerSpeed;
	//m_speed.y -= gravity * frametime;

	
	m_pos = m_CCon.Execute(frametime, m_speed);

	//true = �n�ʂɂ���
	if(m_CCon.IsOnGround() == true)
	{
		m_PlayerAnimation.Play(0);
	}

	
	
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
	
	renderMode = 1;
	Draw(renderMode);

	//�A�j���[�V�����̍Đ�
	m_PlayerAnimation.Update(frametime);
	
	
	renderMode = 0;
	Draw(renderMode);
}


