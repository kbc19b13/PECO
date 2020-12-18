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
	/// <summary>
	/// クマの更新関数
	/// 適切なMoveを呼び出し更新する。
	/// </summary>
	void Update();
	/// <summary>
	/// クマ生成前の初期化を行う
	/// </summary>
	/// アニメーションの初期化
	/// <returns></returns>
	bool Start();

	//状態を作成する関数
public:
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
public:
	/// 通常状態の時の処理を作成。
	/// </summary>
	void ExecuteFSM_Normal();
	/// <summary>
	/// 発見状態の時の処理を作成。
	/// </summary>
	void ExecuteFSM_Discovery();
	/// <summary>
	/// 逃げ状態の時の処理を作成。
	/// </summary>
	void ExecuteFSM_Escape();
	/// <summary>
	/// 帰宅状態の時の処理を作成。
	/// </summary>
	void ExecuteFSM_Return();
	
public:
	/// <summary>
	/// クマの座標に指定されたベクトルを足し算する。
	/// </summary>
	/// <param name="move">足し算するベクトル</param>
	void AddPosition(const CVector3& add)
	{
		m_pos += add;
	}
	/// <summary>
	/// Playerとの距離を判定する関数
	/// </summary>
	float PE_GetDistance();
	/// <summary>
	/// アニメーションの状態を変更
	/// </summary>
	void SetAnimation(const int number)
	{
		m_MoriAnimation.Play(number);
	}
	/// <summary>
	/// 初期座標を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetSavePos() const
	{
		return m_SavePos;
	}
	/// <summary>
	/// 初期座標かの判定結果を設定
	/// </summary>
	/// <param name="issavepos">設定する判定結果</param>
	void SetisSavePos(const bool issavepos)
	{
		m_isSavePos = issavepos;
	}
	const float GetFrameTime() const
	{
		return m_frametime;
	}
	void SetFrameTime(const float frametime)
	{
		m_frametime = frametime;
	}
	void AddTime(const float addtime)
	{
		m_frametime += addtime;
	}

	//初期状態の設定
	void SetState();
public:
	bool IsSavePos() const
	{
		return m_isSavePos;
	}
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		return m_isCotton;
	}

	//ステートの管理関数
private:
	/// <summary>
	/// ステートマシンを実行
	/// </summary>
	void ExecuteFSM();
	/// <summary>


	

protected:

	//初期移動ステート構造体
	enum MoveState {
		State_Circle,		//円移動
		State_LR,			//左右移動
		State_UpDown		//上下移動
	};
	
	//状態管理構造体
	enum State {
		State_Normal,			//通常状態
		State_Discovery,		//発見状態
		State_Escape,			//逃走状態
		State_Return,			//帰宅状態
		State_Restraint,		//拘束状態
		State_Fainted,			//気絶状態
		State_Death				//死亡状態
	};

	MoveState m_movestate = State_Circle;	//移動状態

	State m_state = State_Normal;  //ステート


	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[7];

	bool m_isLive = true;					//生きてる？
	bool m_isCotton = true;					//綿入ってる？
	CVector3 m_SavePos = CVector3::Zero();	//初期座標
	bool m_isSavePos = true;				//初期座標かを判定
	float m_frametime = 0.0f;	//待機時間を計測。

protected:

	std::unique_ptr< IKumaMove >	m_kumamove;	//クマの移動処理。

	Player* m_player = nullptr;
};

