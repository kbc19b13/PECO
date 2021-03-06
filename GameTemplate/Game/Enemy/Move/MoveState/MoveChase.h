#pragma once
#include "Enemy/Move/IKumaMove.h"

#include "Player.h"

/// <summary>
/// クマの逃げる処理
/// </summary>

class MoveChase : public IKumaMove
{
public:
	MoveChase(Kuma* kuma);
	~MoveChase();

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move()override;

private:
	Player* m_player = nullptr;

};