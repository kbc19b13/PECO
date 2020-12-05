#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// クマの逃げる処理
/// </summary>

class MoveNormal : public IKumaMove
{
public:
	MoveNormal(Kuma* kuma);
	~MoveNormal();

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};