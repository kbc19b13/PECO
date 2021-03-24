#include "stdafx.h"
#include "MoveEscape.h"
#include "Enemy/Kuma.h"

MoveEscape::MoveEscape(Kuma* kuma) :
	IKumaMove(kuma)
{
	m_player = Player::P_GetInstance();

	//�A�j���[�V�����̍Đ�
	//�����鎞�̃A�j���[�V�������Đ�
	
}

void MoveEscape::Move()
{
	//������Ԏ��̈ړ��������L�q
	//�ړ������̋L�q
	
	//Discovery����J�ځ�����

	//�EPlayer�ɕ߂܂�ƍS����ԂɑJ�ڂ���
	//Player�̏����ɋL�q���t���O�𗧂Ăď�������H


	//�E��苗�������Ɩ߂��ԂɑJ�ڂ���
	//MoveEscape�N���X�Ȃ��ŏ����ړ������������Move�֐��ɋL�q

	m_speed = { 1.0f, 0.0f, 0.0f };

	//�N�}�̍��W���X�V
	m_kuma->AddPosition(m_speed);

	//Player�ƃN�}�Ƃ̋��������߂āA1000�����Ɩ߂��Ԃɐ؂�ւ���B	
	if (GetDistance(m_player->GetPosition(), m_pos) > 1000.0f)
	{
		//������1000�ȏ�Ȃ�߂��ԂɑJ�ڂ���B
		//�ړ�������߂菈���ɐ؂�ւ���B
		m_kuma->ExecuteFSM_Return();
	}
	
}