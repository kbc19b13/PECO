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
	/// �J�n�֐�
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Update();



private:

	//���x��
	Level m_level;

	int timer = 0;
	int null = 0;

	
	//�N���X�̃��[�h
private:
	Player* m_player = nullptr;

	
};


