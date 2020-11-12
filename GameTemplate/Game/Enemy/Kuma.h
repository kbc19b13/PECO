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


	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[5];

	bool m_isLive = true;				//生きてる？
	bool m_isCotton = true;				//綿入ってる？
	std::unique_ptr< IKumaMove >	m_move;	//クマの移動処理。
};

