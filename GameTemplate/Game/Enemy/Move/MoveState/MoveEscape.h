#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// ƒNƒ}‚Ì“¦‚°‚éˆ—
/// </summary>

class MoveEscape : public IKumaMove
{
public:
	MoveEscape(Kuma* kuma);
	

	/// <summary>
	/// ˆÚ“®ˆ—B
	/// </summary>
	void Move()override;

	

private:
	Player* m_player = nullptr;

};