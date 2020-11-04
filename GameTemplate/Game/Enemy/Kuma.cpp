#include "stdafx.h"
#include "Enemy/Kuma.h"

#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"


bool Kuma::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClip�����[�h(tka�t�@�C���̓ǂݍ���)
	//Animaiton�̏��������s��
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

	
	return true;
}
void Kuma::CreateMoveUpDown()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_move = std::make_unique< KumaMoveUpDown >(this);
}

void Kuma::CreateMoveLR()
{
	m_move = std::make_unique<KumaMoveLR>(this);
}

void Kuma::CreateMoveTrun()
{
	m_move = std::make_unique<KumaMoveCircle>(this);
}

void Kuma::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}
void Kuma::Update()
{

	//�N�}�̈ړ����������s����B
	if (m_move) {
		//�N�}�̈ړ����������s����B
		m_move->Move();
	}

	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	Draw();
}