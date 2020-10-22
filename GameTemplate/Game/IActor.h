#pragma once
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
	/// アクターの座標を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const{
		return m_pos;
	}
	/// <summary>
	/// アクターの座標を設定。
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}

protected:
	CVector3 m_pos = CVector3::Zero();			//座標。
	CQuaternion m_rot = CQuaternion::Identity();//回転クォータニオン。
	CVector3 m_scale = CVector3::One();			//拡大率。
	SkinModel m_model;							//モデルクラス。
};

