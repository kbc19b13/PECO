#pragma once

#include "Move/IKumaMove.h"

/// <summary>
/// 森のクマ
/// </summary>
class Kuma final : public IActor
{  
public:
	
	Kuma()
	{}

	virtual ~Kuma()
	{}

	void Update();

	bool Start();

	void Draw();
	/// <summary>
	/// 上下移動の処理を作成。
	/// </summary>
	void CreateMoveUpDown();

	void CreateMoveLR();

	void CreateMoveTrun();
public:
	
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_speed = movespeed;
	}
	const CVector3& GetMoveSpeed() const
	{
		return m_speed;
	}
	void SetRotation(const CQuaternion& rot)
	{
		m_rot = rot;
	}
	const CQuaternion& GetRotation() const
	{
		return m_rot;
	}
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}

protected:

	enum State {
		State_Normal,
		State_Dying,
		State_Death
	};
	State m_state = State_Normal;  //ステート


	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };
	
	

	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[5];

	bool m_isLive = true;				//生きてる？
	bool m_isCotton = true;				//綿入ってる？
	std::unique_ptr< IKumaMove >	m_move;	//クマの移動処理。
};

