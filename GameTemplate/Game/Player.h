#pragma once

#include "character/CharacterController.h"
#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/animation/AnimationPlayController.h"

class Player : public IActor
{
public:
	Player();
	~Player();

	/// <summary>
	/// 開始処理
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 方向取得処理
	/// </summary>
	void Direction();
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// アニメーション再生
	/// </summary>
	void Anim();
	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void AnimInit();

private:
	////////////////*構造の変数*/////////////////////
	//フレート対応時間計測変数
	float frametime = 0.0f;
	
	//キャラコン
	CharacterController m_CCon;

	//AnimationClip配列とAnimationの変数を追加する
	//アニメーション
	Animation m_PlayerAnimation;
	AnimationClip m_PlayerAnimationClips[1];

	//AnimationPlayController m_animPlayCon;
	
	//////////////////////////////////////////////////
	
	////////////////*方向取得の変数*//////////////////
	//playerの前方向取得
	CVector3 p_mae = CVector3::Front();
	//playerの上方向取得
	CVector3 p_ue = CVector3::Up();
	//playerの右方向取得
	CVector3 p_migi = CVector3::Right();

	//Quaternionを行列に変換
	CMatrix p_rot = CMatrix::Identity();
	//////////////////////////////////////////////////
	
	float lStickY = 0.0f;	//LスティックのY軸情報
	float lStickX = 0.0f;	//LスティックのX軸情報

public:
	/////////Singletonパターン///////////////
	//Playerを一体に限定
	static Player* P_GetInstance()
	{
		return m_instance;
	}
private:
	//シングルトン用ポインタ
	static Player* m_instance;
};

