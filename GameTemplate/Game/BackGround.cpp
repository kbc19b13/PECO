#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
	//comファイルの読み込み
	m_model.Init(L"Assets/modelData/PECO_Mori_Stage.cmo");
	
}

BackGround::~BackGround()
{
	DeleteGO("BackGround");
}

bool BackGround::Start()
{
	//レベルを構築する。
	m_level.Init(L"level/levelStage.tkl", [&](LevelObjectData& objData)
		{
		


		//クラスの処理が入らない
		//レベル配置の通りに座標を配置する
		return true;
		});

	return true;
}

void BackGround::Update()
{
	//ワールド行列の更新。
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