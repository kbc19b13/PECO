#include "stdafx.h"
#include "MoveNormal.h"
#include "Enemy/Kuma.h"

MoveNormal::MoveNormal(Kuma* kuma) :
	IKumaMove(kuma)
{

}
MoveNormal::~MoveNormal()
{

}

void MoveNormal::Move()
{
	m_kuma->AddPosition({ 1.0f, 0.0f, 0.0f });
}