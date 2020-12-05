#pragma once

#include "Move/IKumaMove.h"
class Player;

/// <summary>
/// 森のクマ
/// 敵クマの処理分岐
/// </summary>
class Kuma final : public IActor
{  
public:
	
	Kuma()
	{}

	virtual ~Kuma()
	{}

	void Update();

	/// <summary>
	/// クマ生成前の初期化を行う
	/// </summary>
	/// <returns></returns>
	bool Start();

	/// <summary>
	/// 上下移動の処理を作成。
	/// </summary>
	void CreateMoveUpDown();
	/// <summary>
	/// 左右移動の処理を作成
	/// </summary>
	void CreateMoveLR();
	/// <summary>
	/// 円回転の処理を作成
	/// </summary>
	void CreateMoveTrun();
	/// <summary>
	/// クマの座標に指定されたベクトルを足し算する。
	/// </summary>
	/// <param name="move">足し算するベクトル</param>
	void AddPosition(const CVector3& add)
	{
		m_pos += add;
	}
public:
	
	
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}
private:
	/// <summary>
	/// ステートマシンを実行
	/// </summary>
	void ExecuteFSM();
	/// <summary>
	/// 通常状態の時の処理を実行。
	/// </summary>
	void ExecuteFSM_Normal();
	/// <summary>
	/// 逃げ状態の時の処理を実行。
	/// </summary>
	void ExecuteFSM_Escape();
protected:

	enum State {
		State_Normal,			//通常状態
		State_TransitionEscape,	//逃げに切り替え中の状態
		State_Escape,			//逃げ状態
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

	Player* m_player = nullptr;
};

