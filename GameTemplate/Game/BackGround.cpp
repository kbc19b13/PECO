#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	//comファイルの読み込み
	m_model.Init(L"Assets/modelData/PECO_Stage.cmo");
}

BackGround::~BackGround()
{

}

void BackGround::Update()
{
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
}

void BackGround::Draw()
{
	m_model.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}