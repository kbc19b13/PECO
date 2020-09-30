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
	////レベルを構築する。
	//m_level.Init(L"level/levelStage.tkl", [&](LevelObjectData& objData) {
	//	//オブジェクトを検索
	//	if (objData.EqualObjectName(L"isi")) {

	//		BubbleCreator* isi = NewGO<BubbleCreator>(2, "isi");
	//		isi->Setposition(objData.position);



	//		return true;
	//	}
	//	//オブジェクトを検索
	//	if (objData.EqualObjectName(L"kawa")) {
	//		BackGround* kawa = NewGO<BackGround>(0, "kawa");
	//		kawa->Setposition(objData.position);


	//		return true;
	//	}

	//	//クラスの処理が入らない
	//	//レベル配置の通りに座標を配置する
	//	return

	return true;
}

void BackGround::Update()
{
	//ワールド行列の更新。
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