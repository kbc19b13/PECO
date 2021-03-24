#include "stdafx.h"
#include "PlayerCamera.h"

PlayerCamera::PlayerCamera()
{

}
PlayerCamera::~PlayerCamera()
{

}

bool PlayerCamera::Start()
{
	/// <summary>
	//////////const�ϐ���ݒ�////////////
	/// </summary>
	/// �ݒ� �� set
	/// 
	//�����ʂ�ݒ�
	const float set_far = 10000.0f;


	//Player�̃C���X�^���X���擾
	m_player = Player::P_GetInstance();

	
	g_camera3D.SetFar(set_far);
	
	return true;
}

void PlayerCamera::Update()
{
	//�����_�̍�����ݒ�
	const float set_height = 50.0f;

	//�J�������X�V�B
	//�����_���v�Z����B
	CVector3 target = m_player->GetPosition();
	//��O��position�ɒu��������
	old_pos = Camera_pos;

	CameraUpdate();

	target.y = set_height;
	CVector3 pos = target + Camera_pos;

	g_camera3D.SetTarget(target);
	g_camera3D.SetPosition(pos);
	
	//�J�����̍X�V�B
	g_camera3D.Update();
}
void PlayerCamera::CameraUpdate()
{
	//�J�����̏������ݒ�
	const CVector3 set_Up = { 0.0f,  1.0f,  0.0f };

	//�p�b�h�̓��͂ŃJ��������]
	float rStickX = g_pad[0].GetRStickXF();
	float rStickY = g_pad[0].GetRStickYF();

	//�㉺�̃J������]
	CQuaternion rot;
	rot.SetRotationDeg(set_Up, 0.5f * rStickX);
	rot.Apply(Camera_pos);

	//���E�̃J������]
	CVector3 rotAxis;
	rotAxis.Cross(Camera_pos, { 0.0f, 1.0f, 0.0f });
	rotAxis.Normalize();//�P�ʃx�N�g���ɕω�
	rot.SetRotationDeg(rotAxis, 0.5f * rStickY);
	rot.Apply(Camera_pos);

	//�J�����̉�]�̏�����`�F�b�N����B
	//�����_���王�_�܂ł̃x�N�g���𐳋K������B
	//���K������ƁA�x�N�g���̑傫�����P�ɂȂ�B
	//�傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�Ƃ������ƁB
	CVector3 toPosDir = Camera_pos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.1f) {
		//�J����������������B
		Camera_pos = old_pos;
	}
	else if (toPosDir.y > 0.8f) {
		//�J�����������������B
		Camera_pos = old_pos;
	}
}
