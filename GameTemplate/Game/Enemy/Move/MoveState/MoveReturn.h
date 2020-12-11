#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// ƒNƒ}‚Ì“¦‚°‚éˆ—
/// </summary>

class MoveReturn : public IKumaMove
{
public:
	MoveReturn(Kuma* kuma);
	~MoveReturn();

	/// <summary>
	/// ˆÚ“®ˆ—B
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};