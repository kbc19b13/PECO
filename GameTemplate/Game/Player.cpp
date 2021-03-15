#include "stdafx.h"
#include "Player.h"
#include "Time/mtGameTime.h"
//#include "..//mtEngine/mtStopwatch.h"

//�O���[�o����Player�͈�l����
Player* Player::m_instance = nullptr;

Player::Player()
{
	//�C���X�^���X�̐���
	if (m_instance != nullptr)
	{
		//2�̖ڂ���̓G���[���o��
		std::abort();
	}
	
	//Player���Œ�
	m_instance = this;
}


Player::~Player()
{
	DeleteGO("Player");
}

bool Player::Start()
{
	const float CCon_radius = 30.0f;
	const float height = 160.0f;

	//cmo�t�@�C���̓ǂݍ��݁B
	m_model.Init(L"Assets/modelData/PECO.cmo");
	
	//AnimationClip�����[�h(tka�t�@�C���̓ǂݍ���)
	//Animaiton�̏��������s��
	m_PlayerAnimationClips[0].Load(L"Assets/animData/Walk_PECO.tka");
	m_PlayerAnimationClips[0].SetLoopFlag(true);
	m_PlayerAnimationClips[1].Load(L"Assets/animData/Sneak_PECO.tka");
	m_PlayerAnimationClips[1].SetLoopFlag(true);
	m_PlayerAnimationClips[2].Load(L"Assets/animData/Cat_PECO.tka");
	m_PlayerAnimationClips[2].SetLoopFlag(true);
	m_PlayerAnimationClips[3].Load(L"Assets/animData/Extraction_PECO.tka");
	m_PlayerAnimationClips[3].SetLoopFlag(true);
	//�A�j���[�V�����̏�����
	m_PlayerAnimation.Init(
		//�A�j���[�V�����𗬂��X�L�����f��(�֘A�t��)
		m_model,
		//�A�j���[�V�����N���b�v�̔z��
		m_PlayerAnimationClips,
		//�A�j���[�V�����N���b�v�̐�
		4
	);

	//Player���V���h�E���V�[�o�[�ɂ���B
	m_model.SetShadowReciever(true);

	m_CCon.Init(CCon_radius, height, m_pos);
	
	return true;
}

void Player::Update()
{
	//�ϐ�
	frametime = GameTime().GetFrameDeltaTime();

	//�����̎擾����
	Direction();
	//�ړ�����
	Move();
	//�A�j���[�V�����Đ�
	Anim();

	//�A�j���[�V�����̍Đ�
	m_PlayerAnimation.Update(frametime);

	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	//���[���h�s��̍X�V�B
	m_model.UpdateWorldMatrix(m_pos, m_rot, CVector3::One());
	
	renderMode = enRenderMode_Silhouette;
	Draw(renderMode);

	renderMode = enRenderMode_Normal;
	Draw(renderMode);
}

void Player::Direction()
{
	//Quaternion�̉�]����s��ɕϊ�
	p_rot.MakeRotationFromQuaternion(m_rot);

	//�O�������K���x�N�g���̎擾
	p_mae.x = p_rot.m[2][0];
	p_mae.y = p_rot.m[2][1];
	p_mae.z = p_rot.m[2][2];
	p_mae.Normalize();

	//��������K���x�N�g���̎擾
	p_ue.x = p_rot.m[1][0];
	p_ue.y = p_rot.m[1][1];
	p_ue.z = p_rot.m[1][2];
	p_ue.Normalize();

	//�E�������K���x�N�g���̎擾
	p_migi.x = p_rot.m[0][0];
	p_migi.y = p_rot.m[0][1];
	p_migi.z = p_rot.m[0][2];
	p_migi.Normalize();
}
void Player::Move()
{
	//�萔
	const float playerSpeed = -200.0f;
	const float gravity = 980.0f;

	//�X�e�B�b�N�ł̈ړ�
	float lStickY = g_pad[0].GetLStickYF();
	float lStickX = -g_pad[0].GetLStickXF();

	//�J�����̑O�������ƉE�������擾�B
	CVector3 cameraForward = g_camera3D.GetForward();
	CVector3 cameraRight = g_camera3D.GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_speed.x = 0.0f;
	m_speed.z = 0.0f;
	//p_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	m_speed += cameraForward * lStickY * playerSpeed;	//�������ւ̈ړ����x�����B
	m_speed += cameraRight * lStickX * -playerSpeed;		//�E�����ւ̈ړ����x�����Z�B
	

	if (fabsf(m_speed.x) < 0.001f
		&& fabsf(m_speed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(m_speed.x, m_speed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	m_rot.SetRotation(CVector3::AxisY(), angle);

	//moveSpeed��position�𓮂���
	m_pos += m_speed;
}
void Player::Anim()
{
	m_pos = m_CCon.Execute(frametime, m_speed);

	//true = �n�ʂɂ���
	if(m_CCon.IsOnGround() == true)
	{
		m_PlayerAnimation.Play(0);
	}
	if (g_pad[0].IsPress(enButtonB))
	{
		m_PlayerAnimation.Play(1);
	}
	/*if (g_pad[0].IsPress(enButtonLeft)) {
		m_pos.x += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		m_pos.x -= 5.0f;
	}
	if (g_pad[0].IsPress(enButtonUp)) {
		m_pos.z += 5.0f;
	}
	if (g_pad[0].IsPress(enButtonDown)) {
		m_pos.z -= 5.0f;
	}*/

	
}