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
	////���x�����\�z����B
	//m_level.Init(L"level/levelStage.tkl", [&](LevelObjectData& objData) {
	//	//�I�u�W�F�N�g������
	//	if (objData.EqualObjectName(L"isi")) {

	//		BubbleCreator* isi = NewGO<BubbleCreator>(2, "isi");
	//		isi->Setposition(objData.position);



	//		return true;
	//	}
	//	//�I�u�W�F�N�g������
	//	if (objData.EqualObjectName(L"kawa")) {
	//		BackGround* kawa = NewGO<BackGround>(0, "kawa");
	//		kawa->Setposition(objData.position);


	//		return true;
	//	}

	//	//�N���X�̏���������Ȃ�
	//	//���x���z�u�̒ʂ�ɍ��W��z�u����
	//	return

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
		g_camera3D.GetProjectionMatrix()
	);
}