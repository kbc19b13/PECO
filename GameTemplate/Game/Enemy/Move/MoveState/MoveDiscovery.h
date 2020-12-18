#pragma once
#include "Enemy/Move/IKumaMove.h"

class Player;

/// <summary>
/// クマが逃げる前の待機処理処理
/// </summary>

class MoveDiscovery : public IKumaMove
{
public:
	MoveDiscovery(Kuma* kuma);
	

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move()override;

private:
	

	//クラスのロード
private:
	Player* m_player = nullptr;

};