#pragma once
#include "Enemy/Move/IKumaMove.h"

#include "Player.h"

/// <summary>
/// ƒNƒ}‚Ì“¦‚°‚éˆ—
/// </summary>

class MoveChase : public IKumaMove
{
public:
	MoveChase(Kuma* kuma);
	~MoveChase();

	/// <summary>
	/// ˆÚ“®ˆ—B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};