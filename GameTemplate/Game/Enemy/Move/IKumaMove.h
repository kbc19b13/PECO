#pragma once

class IAcotr;
class Kuma;
class MoveEscape;

/// <summary>
/// クマの移動処理の基底クラス
/// 基本となる変数、関数を所持
/// 移動処理クラスはこのクラスを継承して、作成していく
/// </summary>
class IKumaMove : public IActor
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
	
protected:
	Kuma* m_kuma = nullptr;	//このクラスで移動させているクマ。
	CVector3 m_initPos = CVector3::Zero();		//クマの初期座標。
};

