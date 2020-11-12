#pragma once

class Kuma;
class MoveEscape;

/// <summary>
/// クマの移動処理の基底クラス
/// </summary>
class IKumaMove
{
public:
	IKumaMove(Kuma* kuma) :
		m_kuma(kuma)
	{

	}
	/// <summary>
	/// 移動処理。
	/// </summary>
	virtual void Move() = 0;

	//共通処理
	void KumaUpdate();

	void Escape();

	void ChaseDown();

protected:
	Kuma* m_kuma = nullptr;	//このクラスで移動させているクマ。
	CVector3 m_initPos;		//クマの初期座標。

protected:
	//MoveEscape m_Escape;
};

