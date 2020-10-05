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
	//���x�����\�z����B
	m_level.Init(L"level/levelStage.tkl", [&](LevelObjectData& objData)
		{
		


		//�N���X�̏���������Ȃ�
		//���x���z�u�̒ʂ�ɍ��W��z�u����
		return true;
		});

	return true;
}

void BackGround::Update()
{
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	Draw();
	m_level.Draw();
}

void BackGround::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}