#pragma once

#include "Enemy/Move/IKumaMove.h"
#include "Player.h"

/// <summary>
/// クマの移動処理(上下移動)
/// </summary>
class KumaMoveUpDown : public IKumaMove
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="kuma">このクラスで移動させるクマ</param>
	KumaMoveUpDown(Kuma* kuma);
	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move() override;

private:
	Player* m_player = nullptr;
};

