#include "stdafx.h"
#include "MoveEscape.h"
#include "Enemy/Kuma.h"

MoveEscape::MoveEscape(Kuma* kuma) :
	IKumaMove(kuma)
{

}
MoveEscape::~MoveEscape()
{

}

void MoveEscape::Move()
{
	m_kuma->AddPosition({ 1.0f, 0.0f, 0.0f });
}