#pragma once
#include "Enemy/Move/IKumaMove.h"


/// <summary>
/// ステートパターン
/// ステート管理を行うクラス
/// </summary>
class IMoveState : public IKumaMove
{
public:
	/*
	ステート管理を行う際に先にクラスのロードを行っておくため、
	Start関数、Delete関数を呼ぶことができないので、
	Start = Enter
	Delete = Leave
	として扱う関数を作成する。
	*/

	/// <summary>
	/// 入る関数(状態切り替え時の関数)
	/// </summary>
	virtual void Enter();		
	/// <summary>
	/// 去る関数(状態切り替え時の関数)
	/// </summary>
	virtual void Leave();		
};