#include "stdafx.h"
#include "BackGround.h"



BackGround::BackGround()
{
	//comファイルの読み込み
	m_model.Init(L"Assets/modelData/PECO_Mori_Stage.cmo");
	//地面をシャドウレシーバーにする。
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
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_pos, CQuaternion::Identity(), CVector3::One());
	Draw(0);
	
}