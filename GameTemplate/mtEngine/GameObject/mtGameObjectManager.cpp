#include "Timer/mtEnginePreCompile.h"
#include "GameObject/mtGameObjectManager.h"


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
	//Startを実行
	void mtGameObjectManager::ExecuteFromMainThread()
	{
		//Start
		Start();
	}
	void mtGameObjectManager::ExecuteFromGameThread()
	{

		//更新系の処理。
		{//アップデート。いる
			Update();

			/*
			//事前アップデート。
			PreUpdate();
			//プリレンダリングの更新処理。
			GraphicsEngine().GetPreRender().Update();

			//遅延アップデート。
			PostUpdate();
			//シーングラフを更新。
			UpdateSceneGraph();
			//ライトを更新。
			LightManager().Update();
			//エフェクトを更新。
			GraphicsEngine().GetEffectEngine().Update();
			*/
		}
		/*
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
		*/

		ExecuteDeleteGameObjects();

	}
	/*
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
		int preBufferNo = m_currentDeleteObjectBufferNo;//現在の
		//バッファを切り替え。
		m_currentDeleteObjectBufferNo = 1 ^ m_currentDeleteObjectBufferNo;
		//
		for (mtGameObjectList& goList : m_deleteObjectArray[preBufferNo]) {
			//リスト
			for (IGameObject* go : goList) {
				//実行優先度を受け取る
				GameObjectPrio prio = go->GetPriority();
				//std::vectorのat(要素アクセス)
				mtGameObjectList& goExecList = m_gameObjectListArray.at(prio);
				//std::find(渡された要素を検索)
				auto it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) {
					//削除リストから除外された。
					(*it)->m_isRegistDeadList = false;
					//NewGOで作られているか
					if ((*it)->IsNewFromGameObjectManager()) {
						delete (*it);
					}
				}
				//要素の削除
				goExecList.erase(it);
			}
			//全要素の削除
			goList.clear();
		}
	}
	//初期化
	void mtGameObjectManager::Init(int gameObjectPrioMax)
	{
		//TK_ASSERT(gameObjectPrioMax <= GAME_OBJECT_PRIO_MAX, "ゲームオブジェクトの優先度の最大数が大きすぎます。");
		//キャスト
		m_gameObjectPriorityMax = static_cast<GameObjectPrio>(gameObjectPrioMax);
		//std::List.resaze(要素数を変更する)
		m_gameObjectListArray.resize(gameObjectPrioMax);
		m_deleteObjectArray[0].resize(gameObjectPrioMax);
		m_deleteObjectArray[1].resize(gameObjectPrioMax);
	}
}