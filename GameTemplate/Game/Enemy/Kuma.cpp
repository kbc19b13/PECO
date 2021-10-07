#include "stdafx.h"
#include "Time/mtGameTime.h"
#include "Enemy/Kuma.h"
#include "Player.h"
#include "Move/KumaMoveUpDown.h"
#include "Move/KumaMoveLR.h"
#include "Move/KumaMoveCircle.h"
#include "Move/MoveState/MoveNormal.h"
#include "Move/MoveState/MoveDiscovery.h"
#include "Move/MoveState/MoveEscape.h"
#include "Move/MoveState/MoveReturn.h"
#include "Move/MoveState/MoveChase.h"


bool Kuma::Start()
{
	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/MoriKuma.cmo");

	//AnimationClip�����[�h(tka�t�@�C���̓ǂݍ���)
	//Animaiton�̏��������s��
	//�t�@�C��_�A�j���[�V�����t���[������.txt�ɋL��
	m_MoriAnimationClips[0].Load(L"Assets/animData/idle_Kuma.tka");
	m_MoriAnimationClips[0].SetLoopFlag(true);
	m_MoriAnimationClips[1].Load(L"Assets/animData/Walk_Kuma.tka");
	m_MoriAnimationClips[1].SetLoopFlag(true);
	m_MoriAnimationClips[2].Load(L"Assets/animData/Falldown_Kuma.tka");
	m_MoriAnimationClips[2].SetLoopFlag(true);
	m_MoriAnimationClips[3].Load(L"Assets/animData/Catch_Kuma.tka");
	m_MoriAnimationClips[3].SetLoopFlag(true);
	m_MoriAnimationClips[4].Load(L"Assets/animData/Wriggle_Kuma.tka");
	m_MoriAnimationClips[4].SetLoopFlag(true);
	m_MoriAnimationClips[5].Load(L"Assets/animData/DeathState_Kuma.tka");
	m_MoriAnimationClips[5].SetLoopFlag(true);
	m_MoriAnimationClips[6].Load(L"Assets/animData/Surprise_Kuma.tka");
	m_MoriAnimationClips[6].SetLoopFlag(false);
	//�A�j���[�V�����̏�����
	m_MoriAnimation.Init(
		//�A�j���[�V�����𗬂��X�L�����f��(�֘A�t��)
		m_model,
		//�A�j���[�V�����N���b�v�̔z��
		m_MoriAnimationClips,
		//�A�j���[�V�����N���b�v�̐�
		7
	);

	m_player = Player::P_GetInstance();

	m_states = States_Still;

	return true;
}
////////////////�ړ�����//////////////////////
void Kuma::CreateMoveUpDown()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique< KumaMoveUpDown >(this);
	m_movestate = State_UpDown;
}

void Kuma::CreateMoveLR()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique<KumaMoveLR>(this);
	m_movestate = State_LR;
}

void Kuma::CreateMoveCircle()
{
	//�ړ������̃C���X�^���X���쐬����B
	m_kumamove = std::make_unique<KumaMoveCircle>(this);
	m_movestate = State_Circle;
}
////////////////////////////////////////////
/////////////////��ԏ���///////////////////
void Kuma::ExecuteFSM_Normal()
{
	m_changeStateRequest.nextState = State_Normal;
	m_changeStateRequest.isRequest = true;
}
void Kuma::ExecuteFSM_Discovery()
{
	m_changeStateRequest.nextState = State_Discovery;
	m_changeStateRequest.isRequest = true;
	
}
void Kuma::ExecuteFSM_Escape()
{
	m_changeStateRequest.nextState = State_Escape;
	m_changeStateRequest.isRequest = true;
}
void Kuma::ExecuteFSM_Return()
{
	m_changeStateRequest.nextState = State_Return;
	m_changeStateRequest.isRequest = true;
}
void Kuma::ExecuteFSM_Chase()
{
	m_changeStateRequest.nextState = State_Chase;
	m_changeStateRequest.isRequest = true;
}
////////////////////////////////////////////////
void Kuma::Update()
{
	//�t���[�����[�g�Ή��ϐ�
	float frametime = GameTime().GetFrameDeltaTime();
	
	//�N�}�̈ړ����������s����B
	if (m_kumamove) {
		//�N�}�̈ړ����������s����B
		m_kumamove->Move();
		CommonMove();
	}

	Forward(m_speed);
	OutLook();

	//Player�ƃN�}�Ƃ̋��������߂ď������s��
	//Player�̍��W���擾���鏈��������̂�
	if (GetDistance(m_player->GetPosition(), m_pos) < 100.0f)
	{
		//������100�ȉ��Ȃ瓦����ԂɑJ�ڂ���B
		//�ړ������𓦂��鏈���ɐ؂�ւ���B
		ExecuteFSM_Discovery();
	}
	
	//�X�e�[�g�}�V��
	ExecuteFSM();

	//�A�j���[�V�����̍Đ�
	m_MoriAnimation.Update(frametime);
	//�V���h�E�L���X�^�[�ɓo�^
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	//���W���X�V
	m_model.UpdateWorldMatrix(m_pos, m_rot, m_scale);
	//�ʏ�`��
	Draw(enRenderMode_Normal);
}
void Kuma::ExecuteFSM()
{
	if (m_changeStateRequest.isRequest) {
		m_changeStateRequest.isRequest = false;
		switch (m_changeStateRequest.nextState) {
		case State_Normal:
			//�ʏ���
			switch (m_movestate) {
			case State_Circle:
				//�~�ړ��̏������쐬
				CreateMoveCircle();
				break;

			case State_LR:
				//���E�ړ��̏������쐬
				CreateMoveLR();
				break;

			case State_UpDown:
				//�㉺�ړ��̏������쐬
				CreateMoveUpDown();
				break;
			}
			break;

		case State_Discovery:
			//�������
			m_kumamove = std::make_unique<MoveDiscovery>(this);

			break;

		case State_Escape:
			//�������
			m_kumamove = std::make_unique<MoveEscape>(this);

			break;

		case State_Return:
			//�߂���
			m_kumamove = std::make_unique<MoveReturn>(this);

			break;
		case State_Chase:
			//�ǐՏ��
			m_kumamove = std::make_unique<MoveChase>(this);
			break;
		}
			m_state = m_changeStateRequest.nextState;
	}

}
void Kuma::Forward(const CVector3 speed)
{
	if (fabsf(speed.x) < 0.001f
		&& fabsf(speed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(speed.x, speed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rot.SetRotation(CVector3::AxisY(), angle);

	m_pos += m_speed;
}
void Kuma::OutLook()
{
	//����p������Ƃ�
	//�O�����������߂�
	CVector3 kumaForward = CVector3::AxisZ();
	//��]�ɉ��Z
	m_rot.Multiply(kumaForward);

	//Player�Ɍ������ă��C���΂�
	CVector3 toPlayerDir = m_player->GetPosition() - m_pos;
	//Player�܂ł̋���
	float toPlayerLen = toPlayerDir.Length();
	//���K��
	toPlayerDir.Normalize();

	//���ς��v�Z
	float innerProduct = kumaForward.Dot(toPlayerDir);
	//�p�x���v�Z
	float angle = acos(innerProduct);

	//����p����
	if (fabsf(angle) < CMath::DegToRad(45.0f)
		&& toPlayerLen < 1000.0f)
	{
		//�󋵂�`����
		m_states = States_Found;
		//��Ԃ�؂�ւ���
		ExecuteFSM_Discovery();
	}
}
void Kuma::CommonUpdate()
{
	
}
void Kuma::CommonMove()
{
	//�O�������֐�
	Forward(m_kumamove->GetMoveSpeed());


}
