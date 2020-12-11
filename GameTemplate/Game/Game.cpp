#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "PlayerCamera.h"
#include "Enemy/Kuma.h"

Game::Game()
{

}
Game::~Game()
{
	DeleteGO("Game");
	DeleteGO("Background");
	DeleteGO("Player");
	DeleteGO("Player2");
	DeleteGO("Player3");
	DeleteGO("Enemy");
}
bool Game::Start()
{
	
	
	
	
	
	//レベルを構築する。
	//m_level.Init(L"level/MoriLevel.tkl", false);
	m_level.Init(L"Assets/level/MoriLevel.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"PECO_Mori_Stage"))
			{
				//背景のレベルを生成する
				BackGround* background = NewGO<BackGround>(0, "Stage");
				background->SetPosition(objData.position);
			}
			if (objData.EqualObjectName(L"MoriKuma"))
			{
				//敵クマさんとして生成
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//停止している何も入っていないクマさん
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_LR"))
			{
				//敵クマさんとして生成
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//左右移動の処理を作成する。
				kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_UD"))
			{
				//敵クマさんとして生成
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//上下移動の処理を作成する。
				kuma->CreateMoveUpDown();
				return true;
			}
			
			if (objData.EqualObjectName(L"MoriKuma_Trun"))
			{
				//敵クマさんとして生成
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//円移動の処理を作成する。
				kuma->CreateMoveTrun();
				return true;
			}
			
			//レベル配置の通りに座標を配置する
			return false;
		});
	//Playerを生成
	m_player = NewGO<Player>(0, "Player");
	//Playerを中心とするカメラを生成
	PlayerCamera* p_camera = NewGO<PlayerCamera>(0, "playercamera");

	return true;
 }

void Game::Update()
{
	m_level.Draw();
	
	//シャドウマップ更新
	g_graphicsEngine->GetShadowMap()->Update(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
}