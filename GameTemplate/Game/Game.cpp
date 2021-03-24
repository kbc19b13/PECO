#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "PlayerCamera.h"
#include "Enemy/Kuma.h"

Game::Game()
{
	//2D�J�����̏���ݒ肵�Ă���B
	g_camera2D.SetUpdateProjMatrixFunc(Camera::enUpdateProjMatrixFunc_Ortho);
	g_camera2D.SetWidth(FRAME_BUFFER_W);
	g_camera2D.SetHeight(FRAME_BUFFER_H);
	g_camera2D.SetPosition({ 0.0f, 0.0f, -10.0f });
	g_camera2D.SetTarget(CVector3::Zero());
	g_camera2D.Update();
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
	
	
	
	
	
	//���x�����\�z����B
	//m_level.Init(L"level/MoriLevel.tkl", false);
	m_level.Init(L"Assets/level/MoriLevel.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"PECO_Mori_Stage"))
			{
				//�w�i�̃��x���𐶐�����
				BackGround* background = NewGO<BackGround>(0, "Stage");
				background->SetPosition(objData.position);
			}
			if (objData.EqualObjectName(L"MoriKuma"))
			{
				//�G�N�}����Ƃ��Đ���
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				kuma->SetSavePos(objData.position);
				//��~���Ă��鉽�������Ă��Ȃ��N�}����
				kuma->ExecuteFSM_Normal();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_LR"))
			{
				//�G�N�}����Ƃ��Đ���
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				kuma->SetSavePos(objData.position);
				//���E�ړ��̏������쐬����B
				kuma->CreateMoveLR();
				return true;
			}
			if (objData.EqualObjectName(L"MoriKuma_UD"))
			{
				//�G�N�}����Ƃ��Đ���
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				kuma->SetSavePos(objData.position);
				//�㉺�ړ��̏������쐬����B
				kuma->CreateMoveUpDown();
				return true;
			}
			
			if (objData.EqualObjectName(L"MoriKuma_Trun"))
			{
				//�G�N�}����Ƃ��Đ���
				Kuma* kuma = NewGO<Kuma>(0, "Enemy");
				kuma->SetPosition(objData.position);
				kuma->SetSavePos(objData.position);
				//�~�ړ��̏������쐬����B
				kuma->CreateMoveCircle();
				return true;
			}
			if (objData.EqualObjectName(L"PECO"))
			{
				//Player�̐���
				Player* player = NewGO<Player>(0, "PECO");
				player->SetPosition(objData.position);
				return true;
			}
			
			//���x���z�u�̒ʂ�ɍ��W��z�u����
			return false;
		});
	//Player�𐶐�
	//m_player = NewGO<Player>(0, "Player");
	//Player�𒆐S�Ƃ���J�����𐶐�
	PlayerCamera* p_camera = NewGO<PlayerCamera>(0, "playercamera");

	return true;
 }

void Game::Update()
{
	m_level.Draw();
	
	//�V���h�E�}�b�v�X�V
	g_graphicsEngine->GetShadowMap()->Update(
		{ 1000.0f, 1000.0f, 1000.0f },
		{ 0.0f, 0.0f, 0.0f }
	);
}