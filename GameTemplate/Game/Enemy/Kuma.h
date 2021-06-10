#pragma once

#include "Move/IKumaMove.h"
class Player;

/// <summary>
/// 森のクマ
/// 敵クマの処理分岐
/// </summary>
class Kuma final : public IActor
{  
	//構造体は上位に描こう関数に使用するときにエラーが出る…
protected:
	//初期移動ステート構造体
	enum MoveState {
		State_Circle,			//円移動
		State_LR,				//左右移動
		State_UpDown,			//上下移動
	};
	//発見状況
	enum DiscoverySituation
	{
		States_Still,			//未だ
		States_Found,			//発見した
		States_Discovered		//発見された
	};
	//状態管理構造体
	enum State {
		State_Normal,			//通常状態
		State_Discovery,		//発見状態
		State_Chase,			//追跡状態
		State_Escape,			//逃走状態
		State_Return,			//帰宅状態
		State_Restraint,		//拘束状態
		State_Fainted,			//気絶状態
		State_Death				//死亡状態
	};
	//ステート切り替えリクエスト
	struct ChangeStateRequest {
		State nextState;	//次のステート
		bool isRequest;		//リクエストを受けている？

	};

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
	/// <summary>
	/// 共通処理
	/// </summary>
	void CommonUpdate();
	/// <summary>
	/// 共通移動処理
	/// </summary>
	void CommonMove();
	/// <summary>
	/// 前に向く
	/// </summary>
	void Forward(const CVector3 speed);
	/// <summary>
	/// 視野角の判定を行う
	/// </summary>
	void OutLook();
private://ステートの管理関数
	/// <summary>
	/// ステートマシンを実行
	/// </summary>
	void ExecuteFSM();

public:/*初期移動状態を作成する関数*/
	
	/// /// <summary>
	/// 上下移動の処理を作成。
	/// </summary>
	void CreateMoveUpDown();
	/// <summary>
	/// 左右移動の処理を作成
	/// </summary>
	void CreateMoveLR();
	/// <summary>
	/// 円移動の処理を作成
	/// </summary>
	void CreateMoveCircle();
public:/*状態を作成する関数*/
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
	/// <summary>
	/// 追跡状態の時の処理を作成
	/// </summary>
	void ExecuteFSM_Chase();
	
	
public:/*取得関数*/
	/// <summary>
	/// クマの座標を取得
	/// </summary>
	const CVector3& GetPos() const
	{
		return m_pos;
	}
	/// <summary>
	/// 初期座標を取得。
	/// </summary>
	/// <returns></returns>
	const CVector3& GetSavePos() const
	{
		return m_savePos;
	}
	/// <summary>
/// 現在の状態を取得
/// </summary>
/// <returns></returns>
	const MoveState GetState() const
	{
		return m_movestate;
	}
public:/*設定関数*/
	/// <summary>
	/// アニメーションの状態を設定
	/// </summary>
	void SetAnimation(const int number)
	{
		m_MoriAnimation.Play(number);
	}
	/// <summary>
	/// 初期座標を設定する
	/// </summary>
	void SetSavePos(const CVector3 pos)
	{
		m_savePos = pos;
	}
	/// <summary>
	/// 初期座標かの判定結果を設定
	/// </summary>
	/// <param name="issavepos">設定する判定結果</param>
	void SetisSavePos(const bool issavepos)
	{
		m_isSavePos = issavepos;
	}
	/// <summary>
	/// 発見状態の状況を設定
	/// </summary>
	/// <returns>設定する状況</returns>
	void SetStates(const DiscoverySituation states)
	{
		m_states = states;
	}
	/// <summary>
	/// 発見状態の状況を取得
	/// </summary>
	/// <returns>状況</returns>
	const DiscoverySituation GetStates() const
	{
		return m_states;
	}
	/// <summary>
	/// フレーム時間を取得
	/// </summary>
	/// <returns></returns>
	const float GetFrameTime() const
	{
		return m_frametime;
	}
	/// <summary>
	/// フレーム時間を設定
	/// </summary>
	/// <param name="frametime"></param>
	void SetFrameTime(const float frametime)
	{
		m_frametime = frametime;
	}
	/// <summary>
	/// 現在の状態を設定
	/// </summary>
	MoveState SetState(const MoveState state) {
		m_movestate = state;
	}
public:/*判定関数*/
	/// <summary>
	/// 初期座標判定
	/// </summary>
	/// <returns></returns>
	bool IsSavePos() const
	{
		return m_isSavePos;
	}
	/// <summary>
	/// 生存判定
	/// </summary>
	/// <returns></returns>
	bool IsLive() const
	{
		return m_isLive;
	}
	/// <summary>
	/// 死亡判定
	/// </summary>
	/// <returns></returns>
	bool IsDying() const
	{
		return m_isCotton;
	}

public://加算関数
	/// <summary>
	/// 1フレームの時間を加算
	/// </summary>
	/// <param name="addtime"></param>
	void AddTime(const float addtime)
	{
		m_frametime += addtime;
	}

protected:
	ChangeStateRequest m_changeStateRequest;
	MoveState m_movestate = State_LR;			//移動状態

	State m_state = State_Normal;				//ステート

	DiscoverySituation m_states = States_Still;	//状況

	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_MoriAnimation;
	AnimationClip m_MoriAnimationClips[7];

	bool m_isLive = true;					//生きてる？
	bool m_isCotton = true;					//綿入ってる？
	CVector3 m_savePos = CVector3::Zero();	//初期座標
	bool m_isSavePos = true;				//初期座標かを判定
	float m_frametime = 0.0f;				//待機時間を計測。

protected:

	std::unique_ptr< IKumaMove >	m_kumamove;	//クマの移動処理。

	Player* m_player = nullptr;
};

