#include "stdafx.h"
#include "BackGround.h"



BackGround::BackGround()
{
	//com�t�@�C���̓ǂݍ���
	m_model.Init(L"Assets/modelData/PECO_Mori_Stage.cmo");
	
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
	Draw();
	
}

void BackGround::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix(),
		0
	);
}