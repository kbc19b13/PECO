#include "stdafx.h"
#include "Level.h"
//#include "MapChipRender.h"

using namespace std;



	Level::~Level()
	{
		/*
		for (auto mapChipRender : m_mapChipRenderPtrs) {
			DeleteGO(mapChipRender.second);
		}
		*/
	}

	/*
	CMapChipRender* CLevel::CreateMapChipRenderOrAddRenderObject(const LevelObjectData& objData)
	{
		WNameKey nameKey(objData.name);

		auto itFind = m_mapChipRenderPtrs.find(nameKey.GetHashCode());
		CMapChipRender* pMapChipRender = nullptr;
		if (itFind == m_mapChipRenderPtrs.end()) {
			//�o�^����Ă��Ȃ��I�u�W�F�N�g�B
			auto mapChipRender = NewGO<CMapChipRender>(0);
			pMapChipRender = mapChipRender;
			m_mapChipRenderPtrs.insert({ nameKey.GetHashCode(),mapChipRender });
		}
		else {
			//�`�悷�ׂ��I�u�W�F�N�g�̃C���N�������g�B
			pMapChipRender = itFind->second;
		}
		pMapChipRender->AddRenderObject(objData);
		return pMapChipRender;
	}
	*/

	void Level::Init(
		const wchar_t* levelDataFilePath,
		Level::HookWhenBuildObjectFunc hookFunc
	)
	{
		//�X�P���g�������[�h����B
		Skeleton skeleton;
		skeleton.Load(levelDataFilePath);
		//�\�z�\�z�B
		//0�Ԗڂ̓��[�g�I�u�W�F�N�g�Ȃ̂Ŕ�΂��B
		for (auto i = 1; i < skeleton.GetNumBones(); i++) {
			//�����擾�B
			auto bone = skeleton.GetBone(i);
			if (bone->GetParentId() == 0) {	//�e�����[�g�̏ꍇ�����}�b�v�`�b�v�𐶐�����B
				LevelObjectData objData;
				CVector3 scale;
				bone->CalcWorldTRS(objData.position, objData.rotation, scale);
				//3dsMax�Ƃ͎����Ⴄ�̂ŁA�␳������B
				auto t = objData.position.y;
				objData.position.y = objData.position.z;
				objData.position.z = -t;

				t = objData.rotation.y;
				objData.rotation.y = objData.rotation.z;
				objData.rotation.z = -t;
				objData.name = bone->GetName();

				//std::swap(objData.scale.y, objData.scale.z);

				bool isHook = false;
				if (hookFunc != nullptr) {
					//hook�֐����w�肳��Ă���̂�hook�֐����Ăяo���B
					isHook = hookFunc(objData);
				}
				if (isHook == false) {
					//�t�b�N����Ȃ������̂ŁA�}�b�v�`�b�v���쐬����B
					//���ύX
					//�}�b�v�`�b�v�����_���[���쐬����
					
					auto mapChip = std::make_unique<MapChip>(objData);
					m_mapChipArray.push_back(std::move(mapChip));
					
					//������
					/*
					CreateMapChipRenderOrAddRenderObject(objData);
					*/
				}
			}
		}
		//�}�b�v�`�b�v�����_���[�̏�����
		/*
		for (auto& mapChipRender : m_mapChipRenderPtrs) {
			mapChipRender.second->InitAfterAddAllRenderObjects();
			mapChipRender.second->QueryRenderObjDatas([&](const LevelObjectData& objData) {
				//�t�b�N����Ȃ������̂ŁA�}�b�v�`�b�v���쐬����B
				auto mapChip = std::make_unique<CMapChip>(objData, mapChipRender.second);
				m_mapChipPtrs.push_back(std::move(mapChip));
			});
		}
		*/
	}

	void Level::Draw()
	{
		for (auto& mapChip : m_mapChipArray) {
			mapChip->Draw();
		}
	}
