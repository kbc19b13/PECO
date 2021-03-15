#pragma once
#include "Enemy/Move/IKumaMove.h"

#include "Player.h"

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