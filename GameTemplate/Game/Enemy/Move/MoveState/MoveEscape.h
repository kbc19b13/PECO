#pragma once
#include "IActor.h"
class Player;

/// <summary>
/// クマの逃げる処理
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