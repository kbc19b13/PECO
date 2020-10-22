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
	
	Player* m_player = NewGO<Player>(0, "Player");
	
	PlayerCamera* p_camera = NewGO<PlayerCamera>(0, "playercamera");
	
	//レベルを構築する。
	//m_level.Init(L"level/MoriLevel.tkl", false);
	m_level.Init(L"Assets/level/MoriLevel.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"MoriKuma"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//上下移動の処理を作成する。
				//kuma->CreateMoveUpDown();
				//左右移動の処理を作成する。
				//kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_LR"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//左右移動の処理を作成する。
				kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_UD"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//上下移動の処理を作成する。
				kuma->CreateMoveUpDown();
				return true;
			}
			//レベル配置の通りに座標を配置する
			return false;
		});

	return true;
 }

void Game::Update()
{
	m_level.Draw();


}