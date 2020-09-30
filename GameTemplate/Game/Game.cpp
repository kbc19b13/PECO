#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "PlayerCamera.h"

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
}
bool Game::Start()
{
	
	Player* m_player = NewGO<Player>(0, "Player");
	BackGround* m_background = NewGO<BackGround>(0, "BackGround");
	m_background->SetPosition({ 0.0f, 0.0f, 0.0f });
	PlayerCamera* p_camera = NewGO<PlayerCamera>(0, "playercamera");

	return true;
 }

void Game::Update()
{
	


}