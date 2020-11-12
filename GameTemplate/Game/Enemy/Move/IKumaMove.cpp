#include "stdafx.h"
#include "Enemy/Move/IKumaMove.h"


/// <summary>
/// 共通処理
/// </summary>
void IKumaMove::KumaUpdate()
{
	//クマ逃げる処理
	Escape();

	//クマ追いかける処理
	ChaseDown();

}

void IKumaMove::Escape()
{
	
}

void IKumaMove::ChaseDown()
{

}