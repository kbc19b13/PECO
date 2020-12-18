#include "stdafx.h"
#include "..//mtEngine/mtGameTime.h"
#include "MoveDiscovery.h"
#include "Enemy/Kuma.h"


MoveDiscovery::MoveDiscovery(Kuma* kuma) :
	IKumaMove(kuma)
{
	//�A�j���[�V�����̏���
	//�r�b�N�����Ă���A�j���[�V������
	//�G�t�F�N�g�𗬂��B
	//�r�b�N���A�j���[�V�������Đ�
	m_kuma->SetAnimation(6);
}


void MoveDiscovery::Move()
{
	//Normal����J�ځ��ҋ@�A�x��
	//�I�������Escape�ɑJ�ڂ���B
	//��MoveDiscovery�N���X�Ȃ��ŏ����ړ������������Move�֐��ɋL�q
	//�A�j���[�V�����̍Đ����r�b�N���A�j���[�V�����B
	//�G�t�F�N�g�̍Đ����r�b�N���A�C�R��

	//�ҋ@���̈ړ��������L�q
	//�v���ƑJ�ڂ�kuma�N���X���ӔC�������J�ڃN���X�̍쐬�H
	m_kuma->AddTime(GameTime().GetFrameDeltaTime());
	int a = 0;

	//��b�ҋ@������B
	if (m_kuma->GetFrameTime() >= 1.0f)
	{
		/*�����ɒx����̏�����`��*/

		//�ҋ@���Ԃ������l�ɂ���B
		m_kuma->SetFrameTime(0.0f);
		//�ʏ�A�j���[�V�������Đ�
		m_kuma->SetAnimation(0);

		//������Ԃ��I����ē�����ԂɑJ�ڂ���B
		m_kuma->ExecuteFSM_Escape();
	}
}