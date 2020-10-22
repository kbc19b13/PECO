#pragma once

#include "MapChip.h"
	//class CMapChipRender;

	/*!
	* @brief	�I�u�W�F�N�g���B
	*/
	struct LevelObjectData {
		CVector3 position;		//<���W�B
		CQuaternion rotation;	//!<��]�B
		/*CVector3 scale;�@�@�@ //�g�嗦*/
		const wchar_t* name;	//!<���O�B

		
		//�����œn�����I�u�W�F�N�g���̃I�u�W�F�N�g�����ׂ�
		//objname  ���@���ׂ閼�O
		//���O�������ꍇ��true��Ԃ�
		
		bool EqualObjectName(const wchar_t* objName)
		{
			return wcscmp(objName, name) == 0;
		}

		
		/*
		//���O���O����v���邩���ׂ�B
		
		bool ForwardMatchName(const wchar_t* n)
		{
			auto len = wcslen(n);
			auto namelen = wcslen(name);
			if (len > namelen) {
				//���O�������B�s��v�B
				return false;
			}
			return wcsncmp(n, name, len) == 0;
		}

		*/
	};
	/*!
	 * @brief	���x��
	 *@
	 */
	class Level {
	public:
		~Level();
		/*!
		�`�`�`�}�b�v�`�b�v�̃X�}�[�g�|�C���^�̕ʖ���`�`�`�`
		
		*����*
		�@ std::unique_ptr�͓n���ꂽ���\�[�X�̏��L����B��(���j�[�N)�����Ă���悤��
		�@ �U�����X�}�[�g�|�C���^�B���I�Ɋm�ۂ��ꂽ���\�[�X�́A�C���X�^���X�̎�����
		�@ �s����Ǝ����I�ɔj������܂��B
		*/
		using MapChipPtr = std::unique_ptr<MapChip>;
		/*!
		�`�`�`�I�u�W�F�N�g���r���h���鎞�Ƀt�b�N����֐��I�u�W�F�N�g�̌^�̕ʖ���`�`�`�`
		
		*����*
		 �@�����ɂ̓I�u�W�F�N�g�̏�񂪓n����܂��B
		 �@���̊֐���false��Ԃ��ƁA�I�u�W�F�N�g�̏�񂩂�A�ÓI�I�u�W�F�N�g��MapChip�N���X�̃C���X�^���X��
		 �@��������܂��B
		 �@�I�u�W�F�N�g�̖��O�ȂǂŁA�h�A��W�����v��A�A�C�e���Ȃǂ̓���ȃN���X�̃C���X�^���X�𐶐������Ƃ��ɁA
		 �@�f�t�H���g�ō쐬�����MapChip�N���X�̃C���X�^���X���s�v�ȏꍇ��true��Ԃ��Ă��������B
		 �@�Ⴆ�΁A�t�b�N�֐��̒��ŁA�n���ꂽ�I�u�W�F�N�g�f�[�^�̖��O�̃��f����`�悷��N���X�̃C���X�^���X��
		�@ ���������Ƃ��ɁAfalse��Ԃ��Ă��܂��ƁA�������f������`�悳��邱�ƂɂȂ�܂��B

		*/
		using HookWhenBuildObjectFunc = std::function<bool(LevelObjectData& objData)>;
		/*!
		* @brief	���x�����������B
		*@param[in]	levelDataFilePath		tkl�t�@�C���̃t�@�C���p�X�B
		*@param[in] hookFunc				�I�u�W�F�N�g���쐬���鎞�̏������t�b�N���邽�߂̊֐��I�u�W�F�N�g�B
		*									�t�b�N���Ȃ��Ȃ�nullptr���w�肷��΂悢�A
		*									�ڍׂ�HookWhenBuildObjectFunc�̃R�����g���Q�Ɓ����v
		*/
		void Init(const wchar_t* levelDataFilePath, HookWhenBuildObjectFunc hookFunc);
		
		
		/*!
		* @brief	���x����`��B
		*/
		void Draw();

	private:

		/*
		�}�b�v�`�b�v�����_���[���쐬�o������쐬����or�`�悷�ׂ��I�u�W�F�N�g�̐����C���N�������g����B
		���o�^�̃I�u�W�F�N�g���n���ꂽ�Ƃ��́A�����_���[���쐬���܂��B
		�o�^�ς݂̏ꍇ�́A�}�b�v�`�b�v�����_���[���`�悷�ׂ��I�u�W�F�N�g�̐���
		�C���N�������g����܂��B
	
		CMapChipRender* CreateMapChipRenderOrAddRenderObject(const LevelObjectData& objData);
		*/

	private:
		std::vector<MapChipPtr> m_mapChipArray;		//!<�}�b�v�`�b�v�̉ϒ��z��B
		//std::map< unsigned int, CMapChipRender*> m_mapChipRenderPtrs;	//�}�b�v�`�b�v�����_���[�̉ϒ��z��B
	};
