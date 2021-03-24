#pragma once
#include "GameObject/mtGameObject.h"


/// <summary>
/// アクタークラス
/// </summary>
/// <remarks>
/// このクラスは多くのゲームキャラクターの処理で必要となる、
/// 座標、回転クォータニオン、拡大率、モデル表示機能などの
/// メンバ変数、関数を保持しているクラスです。
/// プレイヤー、エネミーなどのクラスは本クラスを継承して実装しています。
/// </remarks>
class IActor : public IGameObject
{
public:
	/// <summary>
	/// アクターの座標を設定。
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}
	/// <summary>
	/// アクターの座標を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const{
		return m_pos;
	}
	/// <summary>
	/// アクターの移動速度を設定
	/// </summary>
	/// <param name="movespeed"></param>
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_speed = movespeed;
	}
	/// <summary>
	/// アクターの移動速度を取得
	/// </summary>
	/// <returns></returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_speed;
	}
	/// <summary>
	/// アクターの回転を設定
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// アクターの回転を取得
	/// </summary>
	/// <returns></returns>
	const CQuaternion& GetRotation() const
	{
		return m_rot;
	}
	/// <summary>
	/// アクターのモデルデータを取得
	/// </summary>
	/// <returns></returns>
	const SkinModel& GetModel() const
	{
		return m_model;
	}
	/// <summary>
	/// 2点間の距離求める
	/// </summary>
	/// v1→v2に伸びるベクトルを計算
	/// <returns>求めた距離を返す</returns>
	float GetDistance(const CVector3& v1, const CVector3& v2);

public:
	void Draw(EnRenderMode rendermode);

protected:
	CVector3 m_pos = CVector3::Zero();			//座標。
	CQuaternion m_rot = CQuaternion::Identity();//回転クォータニオン。
	CVector3 m_scale = CVector3::One();			//拡大率。
	CVector3 m_speed = CVector3::Zero();		//移動速度。
	SkinModel m_model;							//モデルクラス。

	EnRenderMode renderMode = enRenderMode_Normal;							//０なら通常描画、１ならシルエット描画。
	
	
};

