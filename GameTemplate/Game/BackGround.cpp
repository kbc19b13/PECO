#include "stdafx.h"
#include "BackGround.h"



BackGround::BackGround()
{
	//com�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/PECO_Mori_Stage.cmo");
	//�n�ʂ��V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);
}

BackGround::~BackGround()
{
	DeleteGO("BackGround");
}

bool BackGround::Start()
{
	

	return true;
}

void BackGround::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	Draw(0);
	
}