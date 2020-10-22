#pragma once

class Kuma;
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
protected:
	Kuma* m_kuma = nullptr;	//このクラスで移動させているクマ。
};

