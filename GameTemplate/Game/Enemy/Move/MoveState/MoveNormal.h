#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// ƒNƒ}‚Ì“¦‚°‚éˆ—
/// </summary>

class MoveNormal : public IKumaMove
{
public:
	MoveNormal(Kuma* kuma);
	

	/// <summary>
	/// ˆÚ“®ˆ—B
	/// </summary>
	void Move()override;

private:
private:
	Player* m_player = nullptr;

};