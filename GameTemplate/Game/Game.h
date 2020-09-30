#pragma once
#include "../mtEngine/mtGameObject.h"
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


	int timer = 0;
	int null = 0;
};

