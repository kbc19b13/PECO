#pragma once
#include "IActor.h"
class Player;

/// <summary>
/// �N�}�̓����鏈��
/// </summary>

class MoveEscape : public IActor
{
public:
	MoveEscape();
	~MoveEscape();

	void Update();

private:
	Player* m_player = nullptr;

};