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

		//更新系の処理。
		{

			//事前アップデート。
			//PreUpdate();
			//プリレンダリングの更新処理。
			GraphicsEngine().GetPreRender().Update();

			//アップデート。いる
			Update();

			//遅延アップデート。
			PostUpdate();
			//シーングラフを更新。
			UpdateSceneGraph();
			//ライトを更新。
			LightManager().Update();
			//エフェクトを更新。
			GraphicsEngine().GetEffectEngine().Update();
		}
		//描画系の処理。
		{
			CRenderContext& renderContext = GraphicsEngine().GetRenderContext();
			//画面をクリア
			BeginRender(renderContext);
			//プリレンダリング。
			GraphicsEngine().GetPreRender().Render(renderContext);
			//ディファードシェーディング。
			GraphicsEngine().DefferdShading(renderContext);
			//事前フォワードレンダリング。
			ForwardPreRender(renderContext);
			//フォワードレンダリング。
			ForwardRender(renderContext);
			//ポストエフェクト。
			GraphicsEngine().GetPostEffect().Render(renderContext);
			//2D的なものの描画。
			PostRender(renderContext);
		}

		ExecuteDeleteGameObjects();

	}
	void mtGameObjectManager::UpdateSceneGraph()
	{
		//ワールド行列を更新。
		for (auto transform : m_childrenOfRootTransformList) {
			transform->UpdateWorldMatrixAll();
		}
	}
	*/

	void mtGameObjectManager::ExecuteDeleteGameObjects()
	{
		int preBufferNo = m_currentDeleteObjectBufferNo;
		//バッファを切り替え。
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		for (mtGameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
			for (IGameObject* go : goList) {
				GameObjectPrio prio = go->GetPriority();
				mtGameObjectList& goExecList = m_gameObjectListArray.at(prio);
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) {
					//削除リストから除外された。
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
		//TK_ASSERT(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "ゲームオブジェクトの優先度の最大数が大きすぎます。");
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}
}