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
	
	//���x�����\�z����B
	//m_level.Init(L"level/MoriLevel.tkl", false);
	m_level.Init(L"Assets/level/MoriLevel.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"MoriKuma"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//�㉺�ړ��̏������쐬����B
				//kuma->CreateMoveUpDown();
				//���E�ړ��̏������쐬����B
				//kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_LR"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//���E�ړ��̏������쐬����B
				kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_UD"))
			{
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				//�㉺�ړ��̏������쐬����B
				kuma->CreateMoveUpDown();
				return true;
			}
			//���x���z�u�̒ʂ�ɍ��W��z�u����
			return false;
		});

	return true;
 }

void Game::Update()
{
	m_level.Draw();


}