#pragma once
#include "../mtEngine/mtGameObject.h"
#include "level/Level.h"

class Player;
class PlayerCamera;

class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

private:

	//ƒŒƒxƒ‹
	Level m_level;

	int timer = 0;
	int null = 0;
};

