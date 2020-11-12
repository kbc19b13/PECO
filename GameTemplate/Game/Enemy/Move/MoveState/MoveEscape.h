#pragma once
#include "IActor.h"
class Player;

/// <summary>
/// ƒNƒ}‚Ì“¦‚°‚éˆ—
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