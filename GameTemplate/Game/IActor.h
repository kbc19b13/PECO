#pragma once
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
	/// �A�N�^�[�̍��W���擾�B
	/// </summary>
	/// <returns></returns>
	const CVector3& GetPosition() const{
		return m_pos;
	}
	/// <summary>
	/// �A�N�^�[�̍��W��ݒ�B
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(const CVector3 pos) {
		m_pos = pos;
	}

protected:
	CVector3 m_pos = CVector3::Zero();			//���W�B
	CQuaternion m_rot = CQuaternion::Identity();//��]�N�H�[�^�j�I���B
	CVector3 m_scale = CVector3::One();			//�g�嗦�B
	SkinModel m_model;							//���f���N���X�B
};

