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
	/// <summary>
	/// 開始関数
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新関数
	/// </summary>
	void Update();



private:

	//レベル
	Level m_level;

	int timer = 0;
	int null = 0;

	
	//クラスのロード
private:
	Player* m_player = nullptr;

	
};


