#pragma once
#include "GameObject/mtGameObject.h"


/// <summary>
/// �A�N�^�[�N���X
/// </summary>
/// <remarks>
/// ���̃N���X�͑����̃Q�[���L�����N�^�[�̏����ŕK�v�ƂȂ�A
/// ���W�A��]�N�H�[�^�j�I���A�g�嗦�A���f���\���@�\�Ȃǂ�
/// �����o�ϐ��A�֐���ێ����Ă���N���X�ł��B
/// �v���C���[�A�G�l�~�[�Ȃǂ̃N���X�͖{�N���X���p�����Ď������Ă��܂��B
/// </remarks>
class IActor : public IGameObject
{
public:
	/// <summary>
	/// �A�N�^�[�̍��W��ݒ�B
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}
	/// <summary>
	/// �A�N�^�[�̍��W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const{
		return m_pos;
	}
	/// <summary>
	/// �A�N�^�[�̈ړ����x��ݒ�
	/// </summary>
	/// <param name="movespeed"></param>
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_speed = movespeed;
	}
	/// <summary>
	/// �A�N�^�[�̈ړ����x���擾
	/// </summary>
	/// <returns></returns>
	const CVector3& GetMoveSpeed() const
	{
		return m_speed;
	}
	/// <summary>
	/// �A�N�^�[�̉�]��ݒ�
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(const CQuaternion& rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// �A�N�^�[�̉�]���擾
	/// </summary>
	/// <returns></returns>
	const CQuaternion& GetRotation() const
	{
		return m_rot;
	}
	/// <summary>
	/// �A�N�^�[�̃��f���f�[�^���擾
	/// </summary>
	/// <returns></returns>
	const SkinModel& GetModel() const
	{
		return m_model;
	}
	/// <summary>
	/// 2�_�Ԃ̋������߂�
	/// </summary>
	/// v1��v2�ɐL�т�x�N�g�����v�Z
	/// <returns>���߂�������Ԃ�</returns>
	float GetDistance(const CVector3& v1, const CVector3& v2);

public:
	void Draw(EnRenderMode rendermode);

protected:
	CVector3 m_pos = CVector3::Zero();			//���W�B
	CQuaternion m_rot = CQuaternion::Identity();//��]�N�H�[�^�j�I���B
	CVector3 m_scale = CVector3::One();			//�g�嗦�B
	CVector3 m_speed = CVector3::Zero();		//�ړ����x�B
	SkinModel m_model;							//���f���N���X�B

	EnRenderMode renderMode = enRenderMode_Normal;							//�O�Ȃ�ʏ�`��A�P�Ȃ�V���G�b�g�`��B
	
	
};

