#include "stdafx.h"
#include "MoveEscape.h"
#include "Enemy/Kuma.h"

MoveEscape::MoveEscape(Kuma* kuma) :
	IKumaMove(kuma)
{
	//�A�j���[�V�����̍Đ�
	//�����鎞�̃A�j���[�V�������Đ�
	
}

void MoveEscape::Move()
{
	//������Ԏ��̈ړ��������L�q
	//�ړ������̋L�q
	
	m_kuma->AddPosition({ 1.0f, 0.0f, 0.0f });
}