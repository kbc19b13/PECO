#include "stdafx.h"
#include "..//mtEngine/mtGameTime.h"
#include "Enemy/Kuma.h"
#include "Player.h"
#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"
#include "Move/MoveState/MoveNormal.h"
#include "Move/MoveState/MoveDiscovery.h"
#include "Move/MoveState/MoveEscape.h"
#include "Move/MoveState/MoveReturn.h"


bool Kuma::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClip�����[�h(tka�t�@�C���̓ǂݍ���)
	//Animaiton�̏��������s��
	//�t�@�C��_�A�j���[�V�����t���[������.txt�ɋL��
	m_MoriAnimationClips[0].Load(L"Assets/animData/idle_Kuma.tka");
	m_MoriAnimationClips[0].SetLoopFlag(true);
	m_MoriAnimationClips[1].Load(L"Assets/animData/Walk_Kuma.tka");
	m_MoriAnimationClips[1].SetLoopFlag(true);
	m_MoriAnimationClips[2].Load(L"Assets/animData/Falldown_Kuma.tka");
	m_MoriAnimationClips[2].SetLoopFlag(true);
	m_MoriAnimationClips[3].Load(L"Assets/animData/Catch_Kuma.tka");
	m_MoriAnimationClips[3].SetLoopFlag(true);
	m_MoriAnimationClips[4].Load(L"Assets/animData/Wriggle_Kuma.tka");
	m_MoriAnimationClips[4].SetLoopFlag(true);
	m_MoriAnimationClips[5].Load(L"Assets/animData/DeathState_Kuma.tka");
	m_MoriAnimationClips[5].SetLoopFlag(true);
	m_MoriAnimationClips[6].Load(L"Assets/animData/Surprise_Kuma.tka");
	m_MoriAnimationClips[6].SetLoopFlag(false);
	//�A�j���[�V�����̏�����
	m_MoriAnimation.Init(
		//�A�j���[�V�����𗬂��X�L�����f��(�֘A�t��)
		m_model,
		//�A�j���[�V�����N���b�v�̔z��
		m_MoriAnimationClips,
		//�A�j���[�V�����N���b�v�̐�
		7
	);

	//�V���h�E�L���X�^�[�ɓo�^
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);

	m_player = Player::P_GetInstance();

	return true;
}

float Kuma::PE_GetDistance()
{
	//�v���C���[�Ƃ̋����𔻒肵�āA��苗���ȉ��������瓦����ԂɑJ�ڂ���悤�ɂ��Ă��������B
	CVector3 player_pos = m_player->GetPosition();
	//�v���C���[����G�l�~�[�ɐL�т�x�N�g�����v�Z�B
	CVector3 enemyToPlayerVec = player_pos - m_pos;
	//�v���C���[�ƃG�l�~�[�̋������v�Z�B
	float distance = enemyToPlayerVec.Length();

	return distance;
}

void Kuma::CreateMoveUpDown()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique< KumaMoveUpDown >(this);
	m_movestate = State_UpDown;
}

void Kuma::CreateMoveLR()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique<KumaMoveLR>(this);
	m_movestate = State_LR;
}

void Kuma::CreateMoveTrun()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique<KumaMoveCircle>(this);
	m_movestate = State_Circle;
}

void Kuma::ExecuteFSM_Normal()
{
	//�߂��Ԃ���؂�ւ��ʏ��Ԃ̃C���X�^���X���쐬�B
	m_kumamove = std::make_unique<MoveNormal>(this);
	m_state = State_Normal;
}
void Kuma::ExecuteFSM_Discovery()
{
	//�ҋ@��Ԃ̃C���X�^���X���쐬�B
	m_kumamove = std::make_unique<MoveDiscovery>(this);
	m_state = State_Discovery;
}

void Kuma::ExecuteFSM_Escape()
{
	//������Ԃ̃C���X�^���X���쐬�B
	m_kumamove = std::make_unique<MoveEscape>(this);
	m_state = State_Escape;
}

void Kuma::ExecuteFSM_Return()
{
	//�߂��Ԃ̃C���X�^���X���쐬�B
	m_kumamove = std::make_unique<MoveReturn>(this);
	m_state = State_Return;
}

void Kuma::ExecuteFSM()
{
	switch (m_state) {
	
	case State_Normal:
		//�ʏ���
		ExecuteFSM_Normal();
		break;

	case State_Discovery:
		//�������
		ExecuteFSM_Discovery();
		break;

	case State_Escape:
		//�������
		ExecuteFSM_Escape();
		break;

	case State_Return:
		//�߂���
		ExecuteFSM_Return();
		break;
	
	}

}
void Kuma::Update()
{
	//�֐����݂̂Ŏg�p����ϐ����쐬
	float frametime = GameTime().GetFrameDeltaTime();
	
	//�X�e�[�g�}�V��
	ExecuteFSM();
	//�N�}�̈ړ����������s����B
	if (m_kumamove) {
		//�N�}�̈ړ����������s����B
		m_kumamove->Move();
	}

	//�A�j���[�V�����̍Đ�
	m_MoriAnimation.Update(frametime);

	//���W���X�V
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//�ʏ�`��
	Draw(enRenderMode_Normal);
}