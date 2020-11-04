#pragma once

#include "Enemy/Move/IKumaMove.h"

/// <summary>
/// クマ移動処理
/// </summary>

class KumaMoveCircle : public IKumaMove
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// /// <param name="kuma">このクラスで移動させるクマ</param>
	KumaMoveCircle(Kuma* kuma);
	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move() override;
protected:
	CVector3 m_Speed;		// 速度
	float m_Radius;		// 半径(描画用)
	float m_Angle;		// 向きの角度
	
};

