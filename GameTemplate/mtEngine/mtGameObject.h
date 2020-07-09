//�Q�[���I�u�W�F�N�g�̊��N���X

#pragma once

namespace mtEngine {
	//?
	class mtGameObjectManager;
	typedef unsigned char	GameObjectPrio;//�D��x
	//typedef�ʖ���`

	class IGameObject
	{
	public:
		/*
		�R���X�g���N�^������

		�D��x
		�X�^�[�g���Ă��邩
		����ł��Ȃ���
		NewGO�ō��ꂽ��
		*/
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		/*!
		 *@brief	�f�X�g���N�^
		 */
		virtual ~IGameObject()
		{
		}

		/*!
	*@brief	Update�̒��O�ŌĂ΂��J�n�����B
	*@details
	* �{�֐���true��Ԃ��ƃQ�[���I�u�W�F�N�g�̏��������������Ɣ��f�����</br>
	* Update�֐����Ă΂�o���܂��Btrue��Ԃ��Ĉȍ~��Start�֐��͌Ă΂�Ȃ��Ȃ�܂��B</br>
	* �Q�[���I�u�W�F�N�g�̏������ɕ����t���[��������ꍇ�Ȃǂ�false��Ԃ��āA�������X�e�b�v�Ȃǂ��g����</br>
	* �K�؂ɏ��������s���Ă��������B
	*/
		virtual bool Start() { return true; }
		/*!
		 *@brief	�X�V����
		 */
		virtual void Update() {}

		/*!
	 *@brief	�폜�����Ƃ��ɌĂ΂��B
	 *@details	CGameManager::DeleteGameObject���Ă񂾂Ƃ��Ɏ��s����܂��B
	 * �f�X�g���N�^���O�Ɏ��s����܂��B
	 */
		virtual void OnDestroy() {}
		/*!
		*@brief	���s�D��x���擾�B
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
		/*!
		*@brief	���S�t���O�𗧂Ă�B
			* @details
			* ���̊֐��̓G���W���̊O����͎��s���Ȃ��ł��������B
		*/
			void SetDeadMark()
		{
			m_isDead = true;
		}
		/*!
		*@brief	���S����B
		*/
		bool IsDead() const
		{
			return m_isDead;
		}
		/*!
		*@brief Start�֐������������H
		*/
		virtual bool IsStart() const
		{
			return m_isStart;
		}
		/*!
		*@brief �A�N�e�B�u���ǂ����𔻒�B
		*/
		bool IsActive() const
		{
			return m_isActive;
		}
		/*!
		*@brief �A�N�e�B�u�t���O��ݒ�B
		*/
		void SetActiveFlag(bool flag)
		{
			m_isActive = flag;
		}
		/*!
		*@brief �^�O��ݒ�B
		*/
		void SetTags(unsigned int tags)
		{
			m_tags = tags;
		}
		/*!
		*@brief �^�O���擾�B
		*/
		unsigned int GetTags() const
		{
			return m_tags;
		}
		/*
		*@brief Update���Ă�ł������󋵂�����
		*/
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Update();
			}
		}
		/*
		*@brief Start���Ă�ł������󋵂�����
		*/
		void StartWrapper()
		{
			if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
				if (Start()) {
					//���������������B
					m_isStart = true;
				}
			}
		}
		/*
		*@brief OnDestroy���Ă�ł������󋵂�����
		*/
		void OnDestroyWrapper()
		{

			OnDestroy();

		}
		/*
		*@brief NewGO�Ő������ꂽ�̂�true��n��
		*/
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		/*
		*@brief NewGO�Ő�������Ă��邩�̔���
		*/
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}


		friend class mtGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<���s�D��x�B
		bool m_isStart;						//!<Start�̊J�n�t���O�B
		bool m_isDead;						//!<���S�t���O�B
		bool m_isRegistDeadList = false;	//!<���S���X�g�ɓo�^�B
		bool m_isNewFromGameObjectManager;	//!<GameObjectManager��new���ꂽ�B
		bool m_isRegist = false;			//!<GameObjectManager�ɓo�^����Ă���H
		bool m_isActive = true;				//!<Active�t���O_true�Ȃ�Update���Ă΂��B
		unsigned int m_tags = 0;			//!<�^�O�B
		unsigned int m_nameKey = 0;			//!<���O�L�[�B

	};

}