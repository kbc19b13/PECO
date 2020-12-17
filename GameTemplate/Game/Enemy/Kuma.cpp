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
	m_MoriAnimationClips[0].Load(L"Assets/animData/Walk_Kuma.tka");
	m_MoriAnimationClips[0].SetLoopFlag(true);
	m_MoriAnimationClips[1].Load(L"Assets/animData/Falldown_Kuma.tka");
	m_MoriAnimationClips[1].SetLoopFlag(true);
	m_MoriAnimationClips[2].Load(L"Assets/animData/Catch_Kuma.tka");
	m_MoriAnimationClips[2].SetLoopFlag(true);
	m_MoriAnimationClips[3].Load(L"Assets/animData/Wriggle_Kuma.tka");
	m_MoriAnimationClips[3].SetLoopFlag(true);
	m_MoriAnimationClips[4].Load(L"Assets/animData/DeathState_Kuma.tka");
	m_MoriAnimationClips[4].SetLoopFlag(true);
	//�A�j���[�V�����̏�����
	m_MoriAnimation.Init(
		//�A�j���[�V�����𗬂��X�L�����f��(�֘A�t��)
		m_model,
		//�A�j���[�V�����N���b�v�̔z��
		m_MoriAnimationClips,
		//�A�j���[�V�����N���b�v�̐�
		5
	);

	//SavePos = GetPosition();

	m_player = Player::P_GetInstance();

	return true;
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
	//Return����J�ځ��ʏ�

	//�v���C���[�Ƃ̋����𔻒肵�āA��苗���ȉ��������瓦����ԂɑJ�ڂ���悤�ɂ��Ă��������B
	CVector3 player_pos = m_player->GetPosition();
	//�v���C���[����G�l�~�[�ɐL�т�x�N�g�����v�Z�B
	CVector3 enemyToPlayerVec = player_pos - m_pos;
	//�v���C���[�ƃG�l�~�[�̋������v�Z�B
	float distance = enemyToPlayerVec.Length();
	if (distance < 100.0f)
	{
		//������100�ȉ��Ȃ瓦����ԂɑJ�ڂ���B
		//�ړ������𓦂��鏈���ɐ؂�ւ���B
		m_kumamove = std::make_unique<MoveDiscovery>(this);
		m_state = State_Discovery;
	}

}
void Kuma::ExecuteFSM_Discovery()
{
	//Normal����J�ځ��ҋ@�A�x��
	//�I�������Escape�ɑJ�ڂ���B
	//��MoveDiscovery�N���X�Ȃ��ŏ����ړ������������Move�֐��ɋL�q
	//�A�j���[�V�����̍Đ����r�b�N���A�j���[�V�����B
	//�G�t�F�N�g�̍Đ����r�b�N���A�C�R��

	//�v���ƑJ�ڂ�kuma�N���X���ӔC�������J�ڃN���X�̍쐬�H
	m_frametime += GameTime().GetFrameDeltaTime();

	if (m_frametime >= 1.0f)
	{
		//�����ɒx����̏�����`��
		//������Ԃ��I����ē�����ԂɑJ�ڂ���B
		m_kumamove = std::make_unique<MoveEscape>(this);
		m_state = State_Escape;

		m_frametime = 0.0f;
	}

}

void Kuma::ExecuteFSM_Escape()
{
	//Discovery����J�ځ�����

	//�EPlayer�ɕ߂܂�ƍS����ԂɑJ�ڂ���
	//Player�̏����ɋL�q���t���O�𗧂Ăď�������H


	//�E��苗�������Ɩ߂��ԂɑJ�ڂ���
	//MoveEscape�N���X�Ȃ��ŏ����ړ������������Move�֐��ɋL�q
	
	//�v���C���[�Ƃ̋����𔻒肵�āA��苗���ȉ��������瓦����ԂɑJ�ڂ���悤�ɂ��Ă��������B
	CVector3 player_pos = m_player->GetPosition();
	//�v���C���[����G�l�~�[�ɐL�т�x�N�g�����v�Z�B
	CVector3 enemyToPlayerVec = player_pos - m_pos;
	//�v���C���[�ƃG�l�~�[�̋������v�Z�B
	float distance = enemyToPlayerVec.Length();
		
	if( distance > 1000.0f )
	{
		//������100�ȏ�Ȃ�ʏ��ԂɑJ�ڂ���B
		//�ړ�������ʏ폈���ɐ؂�ւ���B
		m_kumamove = std::make_unique<MoveReturn>(this);
		m_state = State_Return;
	}
	

}

void Kuma::ExecuteFSM_Return()
{
	//�A���Ԃ̏���
	
	//�������W�ɂ��邩���肷��
	if (m_isSavePos) {
		m_kumamove = std::make_unique<MoveNormal>(this);
		m_state = State_Normal;
	}
}

void Kuma::ExecuteFSM()
{
	switch (m_state) {
	
	case State_Normal:
		//�ʏ���
		ExecuteFSM_Normal();
		
		//������Ԃɖ߂������ɔ�����s���c
		/*
			//�ʏ��Ԃɖ߂������̈ړ���ԂɏC��
			switch (m_movestate) {
			case State_Circle:
				CreateMoveTrun();
				break;

			case State_LR:
				CreateMoveLR();
				break;

			case State_UpDown:
				CreateMoveUpDown();
				break;

			}
		*/
		

		break;

	case State_Discovery:
		//�������
		ExecuteFSM_Discovery();
		break;

	case State_Escape:
		//�������
		ExecuteFSM_Escape();
		break;
	
	}

}
void Kuma::Update()
{
	//�N�}�̈ړ����������s����B
	if (m_kumamove) {
		//�N�}�̈ړ����������s����B
		m_kumamove->Move();
	}
	ExecuteFSM();
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	Draw(enRenderMode_Normal);
}