#pragma once


#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "../GameObject/mtGameObject.h"
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include "../util/mtUtil.h"
#include "../graphics/Draw/Sprite.h"

/*!
	*@brief	CGameObject�̃}�l�[�W��
	*/
class mtGameObjectManager
{
private:
	mtGameObjectManager();
	~mtGameObjectManager()
	{
	}
	/*!
*@brief	�Q�[���I�u�W�F�N�g�̖��O�L�[���쐬�B
	�ÓI�֐��@namespace�ŌĂяo����
*/
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		//�f�t�H���g�̖��O�@���@����`
		static const unsigned int defaultNameKey = CUtil::MakeHash("Undefined");	//���O�L�[�B
		unsigned int hash;
		//���O�𖢒�`�ɂ���
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		//�����̖��O��Ԃ�
		else {
			hash = CUtil::MakeHash(objectName);
		}
		return hash;
	}
public:
	/*!
	*@brief	�C���X�^���X�̎擾�B
	*///�ÓI�����o�֐�(�ǂ�����ł��Ăяo����)
	static mtGameObjectManager& Instance()
	{
		//���肵���O���[�o���ϐ�
		static mtGameObjectManager instance;
		return instance;
	}
	/// ���C���X���b�h����Ă΂����s�����B
		/// </summary//�T�v>
	void ExecuteFromMainThread();//Start
	/*!
	*@brief	�Q�[���X���b�h����Ă΂����s�����B
	*/
	void ExecuteFromGameThread();//Updeta
	/// <summary>
	/// todo �`��X���b�h����Ă΂����s����
	/// </summary>
	//void ExecuteFromDrawThread();//Draw
	/*!
	*@brief	�������B
	*@param[in]	gameObjectPrioMax	�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B(255�܂�)
	*/
	void Init(int gameObjectPrioMax);
	/*!
		*@brief	�Q�[���I�u�W�F�N�g�̒ǉ��B
		*@param[in]	prio			���s�D�揇�ʁB
		*@param[in] go				�Q�[���I�u�W�F�N�g
		*@param[in] objectName		�I�u�W�F�N�g��
		*/
	void AddGameObject(GameObjectPrio prio, IGameObject* go, const char* objectName = nullptr)
	{
		//����3�̃I�u�W�F�N�g��
		//�����̂Ȃ��߂�l(void) = �I�u�W�F�N�g���͕Ԃ��Ȃ�
		(void)objectName;
		//GameObjectManager�ɓo�^����Ă��邩
		if (!go->m_isRegist) {
			//go->Awake();//�@�܂���(@^^)/~~~
			//�n�b�V���l�@���@���������A������萔���̂ق�������
			//���O�𐔒l�Ƃ��ĕۊ�
			unsigned int hash = MakeGameObjectNameKey(objectName);
			//at�@�� <vector>�v�f�A�N�Z�X.<list>�����ɗv�f��ǉ�����
			m_gameObjectListArray.at(prio).push_back(go);
			//GameObjectManager�ɓo�^����Ă���
			go->m_isRegist = true;
			//����1�̎��s�D��x��ݒ�
			go->m_priority = prio;
			//Start�͂܂�����Ă��Ȃ�
			go->m_isStart = false;
			//MakeGameObjectNameKey()�̖߂�l���L�^
			go->m_nameKey = hash;

			if (go->m_isDead) {
				//���S�t���O�������Ă���B
				//�폜���X�g�ɓ����Ă����炻�����珜������B
				go->m_isDead = false;
			}

		}
	}
	/*!
			*@brief	�Q�[���I�u�W�F�N�g��new
			*@details
			* ���̊֐����g�p����new�����I�u�W�F�N�g�͕K��DeleteGameObject�����s���邱�Ƃ�delete����܂��B
			*@param[in]	prio		���s�D�揇�ʁB
			*@param[in]	objectName	�I�u�W�F�N�g���B
			*/
	template<class T, class... TArgs>	//�e���v��
	T* NewGameObject(GameObjectPrio prigo, const char* objectName)
	{
		/*
		�e���v���[�g���킩��Ȃ��Ȃ�����
		https://qiita.com/hal1437/items/b6deb22a88c76eeaf90c
		*/
		(void*)objectName;
		//TK_ASSERT(prigo <= m_gameObjectPriorityMax, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
		T* newObject = new T();

		//newObject->Awake();
			
		newObject->SetMarkNewFromGameObjectManager();
		//at�@�� <vector>�v�f�A�N�Z�X.<list>�����ɗv�f��ǉ�����
		m_gameObjectListArray.at(prigo).push_back(newObject);
		//�n�b�V���l�@���@���������A������萔���̂ق�������
		//���O�𐔒l�Ƃ��ĕۊ�
		unsigned int hash = MakeGameObjectNameKey(objectName);
		//GameObjectManager�ɓo�^����Ă���
		newObject->m_isRegist = true;
		//����1�̎��s�D��x��ݒ�
		newObject->m_priority = prigo;
		//MakeGameObjectNameKey()�̖߂�l���L�^
		newObject->m_nameKey = hash;

		//�ݒ肵���l��Ԃ�
		return newObject;
	}
	/*!
		*@brief	�Q�[���I�u�W�F�N�g�̍폜�B
		*/
	void DeleteGameObject(IGameObject* gameObject)
	{
		if (gameObject != nullptr
			&& gameObject->m_isRegist
			) {
			gameObject->SetDeadMark();
			gameObject->OnDestroyWrapper();
			gameObject->m_isRegist = false;
			gameObject->m_isRegistDeadList = true;

			m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
			gameObject = nullptr;
		}
	}
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̌����B
	*@details
	* �d����I
	*@param[in]	objectName		�I�u�W�F�N�g���B
	*/
	template<class T>
	T* FindGameObject(const char* objectName, bool enableErrorMessage)
	{
		unsigned int nameKey = CUtil::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//�������B
					T* p = dynamic_cast<T*>(go);
					if (p == nullptr && enableErrorMessage == true) {
						//�^�ϊ��Ɏ��s�B

						//TK_WARNING_MESSAGE_BOX(
						//	"FingGameObject �F �^�ϊ��Ɏ��s���܂����B�e���v���[�g�������m�F���Ă��������BtypeName = %s, objectName = %s",
						//	typeid(T).name(),
						//	objectName
						//);
					}
					return p;
				}
			}
		}
		if (enableErrorMessage == true) {
			/*TK_WARNING_MESSAGE_BOX("FindGO�֐��Ɏw�肳�ꂽ���O�̃C���X�^���X�������邱�Ƃ��ł��܂���ł����B\n"
				"���O���Ԉ���Ă��Ȃ����m�F�����ĉ������B\n"
				"\n\n�������ꂽ���O �y%s�z\n", objectName);*/
		}
		//������Ȃ������B
		return nullptr;
	}
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = CUtil::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//�������B
					T* p = dynamic_cast<T*>(go);
					if (func(p) == false) {
						//�N�G�����f�B
						return;
					}
				}
			}
		}
	}
private:
	/*!
	*@brief	�Q�[���I�u�W�F�N�g�̍폜�����s�B
	*/
	void ExecuteDeleteGameObjects();
	/*!
	*@brief	�V�[���O���t�̍X�V�B
	*/
	void UpdateSceneGraph();

	void Start();
	void Update();
	void Draw();
		
private:
	typedef std::list<IGameObject*>	mtGameObjectList;
	std::vector<mtGameObjectList>	m_gameObjectListArray;					//!<�Q�[���I�u�W�F�N�g�̗D��x�t�����X�g�B
	std::vector<mtGameObjectList>	m_deleteObjectArray[2];					//!<�폜����I�u�W�F�N�g�̃��X�g�B�폜�������s���Ă���Œ���DeleteGameObject���Ă΂��\���������̂ŁA�_�u���o�b�t�@���B
	GameObjectPrio					m_gameObjectPriorityMax;				//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔�B
	int								m_currentDeleteObjectBufferNo = 0;		//!<���݂̍폜�I�u�W�F�N�g�̃o�b�t�@�ԍ��B
	static const unsigned char 		GAME_OBJECT_PRIO_MAX = 255;				//!<�Q�[���I�u�W�F�N�g�̗D��x�̍ő�l�B
	
	unsigned int					gameObjectPrioMax = 32;					//�D��x�̍ő吔

	Sprite m_copyMainRtToFrameBufferSprite;
};

//�V���O���g���i�C���X�^���X�擾�j
static inline mtGameObjectManager& GameObjectManager()
{
	return mtGameObjectManager::Instance();
}
/*!
*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
*@details
* ���O�̌��������邽�ߒx���ł��B
*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
*@param[in] enableErrorMessage	�G���[���b�Z�[�W���L���H
*�@�Ăяo������nullptr�̔�����s�������ꍇ�́A��������false���w�肵�āA�G���[���b�Z�[�W�̏����𖳌��ɂ��Ă��������B
*
*@return ���������C���X�^���X�̃A�h���X�B������Ȃ������ꍇ��nullptr��Ԃ��B
*/
template<class T>
static inline T* FindGO(const char* objectName, bool enableErrorMessage = true)
{
	return GameObjectManager().FindGameObject<T>(objectName, enableErrorMessage);
}
/*!
*@brief	�Q�[���I�u�W�F�N�g�̌����̃w���p�[�֐��B
*@details
* �����̃Q�[���I�u�W�F�N�g�ɑS�Ăɑ΂��āA�N�G�����s�������ꍇ�Ɏg�p���Ă��������B
*@param[in]	objectName	�Q�[���I�u�W�F�N�g�̖��O�B
*@param[in]	func		�Q�[���I�u�W�F�N�g�����������Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
*/
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
{
	return GameObjectManager().FindGameObjects<T>(objectName, func);
}
/*!
	*@brief	�Q�[���I�u�W�F�N�g�����̃w���p�[�֐��B
	*@param[in]	priority	�v���C�I���e�B = ���s�D��x
	*@param[in]	objectName	�I�u�W�F�N�g���B(NULL�̎w��j
	*@details
	�悭����R���p�C���G���[�@�悭����R���p�C���G���[�@�悭����R���p�C���G���[�@�悭����R���p�C���G���[
	�p
	�p
	�p�@�@�@  �y�P�z public IGameObject��Y��ĂȂ��H
	�p�@�@�@  �y�Q�z #include���Ă�H
	�p
	�p
	�悭����R���p�C���G���[�@�悭����R���p�C���G���[�@�悭����R���p�C���G���[�@�悭����R���p�C���G���[
	*/
	template<class T>
	static inline T* NewGO(
	int priority, 
	const char* objectName = nullptr, 
	typename T::IGameObjectIsBase* = nullptr
)
{
	return GameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
}

/*!
	*@brief	�Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐��B
	* NewGO���g�p���č쐬�����I�u�W�F�N�g�͕K��DeleteGO�����s����悤�ɁB
	*@param[in]	go		�폜����Q�[���I�u�W�F�N�g�B
	*/
static inline void DeleteGO(IGameObject* go)
{
	GameObjectManager().DeleteGameObject(go);
}
/*!
	*@brief	�Q�[���I�u�W�F�N�g�폜�̃w���p�[�֐��B
	* NewGO���g�p���č쐬�����I�u�W�F�N�g�͕K��DeleteGO�����s����悤�ɁB
	*@details
	* ���O�̌��������邽�ߒx���ł��B
	*@param[in]	objectName		�폜����Q�[���I�u�W�F�N�g�̖��O�B
	*/
static inline void DeleteGO(const char* objectName)
{
	IGameObject* go = FindGO<IGameObject>(objectName);
	GameObjectManager().DeleteGameObject(go);
}
/*!
*@brief	�Q�[���I�u�W�F�N�g�𖼑O�w��ō폜�B
*@details
* ���O�������s���邽�ߒx���ł��B
*@param[in]	objectName		�폜����Q�[���I�u�W�F�N�g�̖��O�B
*/
static inline void DeleteGOs(const char* objectName)
{
	QueryGOs<IGameObject>(objectName, [](auto go) {
		DeleteGO(go);
		return true;
		});
}

#endif // _CGAMEOBJECTMANAGER_H_