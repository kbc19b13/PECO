#pragma once

#include "Enemy/Move/IKumaMove.h"

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
protected:
	CVector3 m_initPos;		//クマの初期座標。
};

