#include "mtGameObjectManager.h"
#include "../Game/stdafx.h"


namespace mtEngine {
	void mtGameObjectManager::Start()
	{
		for (mtGameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->StartWrapper();
			}
		}
	}
	void mtGameObjectManager::Update()
	{
		for (mtGameObjectList objList : m_gameObjectListArray) {
			for (IGameObject* obj : objList) {
				obj->UpdateWrapper();
			}
		}
	}
	void mtGameObjectManager::ExecuteFromMainThread()
	{
		//Start
		Start();
	}
	/*
	void mtGameObjectManager::ExecuteFromGameThread()
	{

		//�X�V�n�̏����B
		{

			//���O�A�b�v�f�[�g�B
			//PreUpdate();
			//�v�������_�����O�̍X�V�����B
			GraphicsEngine().GetPreRender().Update();

			//�A�b�v�f�[�g�B����
			Update();

			//�x���A�b�v�f�[�g�B
			PostUpdate();
			//�V�[���O���t���X�V�B
			UpdateSceneGraph();
			//���C�g���X�V�B
			LightManager().Update();
			//�G�t�F�N�g���X�V�B
			GraphicsEngine().GetEffectEngine().Update();
		}
		//�`��n�̏����B
		{
			CRenderContext& renderContext = GraphicsEngine().GetRenderContext();
			//��ʂ��N���A
			BeginRender(renderContext);
			//�v�������_�����O�B
			GraphicsEngine().GetPreRender().Render(renderContext);
			//�f�B�t�@�[�h�V�F�[�f�B���O�B
			GraphicsEngine().DefferdShading(renderContext);
			//���O�t�H���[�h�����_�����O�B
			ForwardPreRender(renderContext);
			//�t�H���[�h�����_�����O�B
			ForwardRender(renderContext);
			//�|�X�g�G�t�F�N�g�B
			GraphicsEngine().GetPostEffect().Render(renderContext);
			//2D�I�Ȃ��̂̕`��B
			PostRender(renderContext);
		}

		ExecuteDeleteGameObjects();

	}
	void mtGameObjectManager::UpdateSceneGraph()
	{
		//���[���h�s����X�V�B
		for (auto transform : m_childrenOfRootTransformList) {
			transform->UpdateWorldMatrixAll();
		}
	}
	*/

	void mtGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//�o�b�t�@��؂�ւ��B
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (mtGameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
			for (IGameObject* go : goList) {
				GameObjectPrio prio = go->GetPriority();
				mtGameObjectList& goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) {
					//�폜���X�g���珜�O���ꂽ�B
					(*it)->m_isRegistDeadList = false;
					if ((*it)->IsNewFromGameObjectManager()) {
						delete (*it);
					}
				}
				goExecList.erase(it);
			}
			goList.clear();
		}
	}

	void mtGameObjectManager::Init(int gameObjectPrioMax)
	{
		//TK_ASSERT(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "�Q�[���I�u�W�F�N�g�̗D��x�̍ő吔���傫�����܂��B");
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}
}