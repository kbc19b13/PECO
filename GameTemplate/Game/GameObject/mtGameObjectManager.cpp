#include "stdafx.h"
#include "mtGameObjectManager.h"


mtGameObjectManager::mtGameObjectManager()
{
	/*
	Initで初期化してもいい
	エンジンが大きくなったり
	初期化するものが多くなるとInitのほうがいいかも
	using int型でメモリ節約
	優先度の指定最大32
	*/
	m_gameObjectListArray.resize(gameObjectPrioMax);
	m_deleteObjectArray[0].resize(gameObjectPrioMax);
	m_deleteObjectArray[1].resize(gameObjectPrioMax);
}

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
		メインレンダリングターゲットを作成するコードをどこに作成するか

			Forwordレンダリングでメインレンダリングターゲットと入れ替えているコードがあるのでそこを
			ゲームオブジェクトマネージャークラスを参照して直す

			参考プログラムの方のビューポートの作成を調べる
			*/

			//PostRender()、
		//レンダリングターゲットをフレームバッファに戻す。
		/*
				void Game::ChangeRenderTarget(ID3D11DeviceContext* d3dDeviceContext, RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
				{
				ChangeRenderTarget(
					d3dDeviceContext,
					renderTarget->GetRenderTargetView(),
					renderTarget->GetDepthStensilView(),
					viewport
				);
			}
			void Game::ChangeRenderTarget
			(
				ID3D11DeviceContext* d3dDeviceContext,
				ID3D11RenderTargetView* renderTarget,
				ID3D11DepthStencilView* depthStensil,
				D3D11_VIEWPORT* viewport
			)
			{
				ID3D11RenderTargetView* rtTbl[] = {
					renderTarget
			};
			//レンダリングターゲットの切り替え。
			d3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
			if (viewport != nullptr) {
				//ビューポートが指定されていたら、ビューポートも変更する。
				d3dDeviceContext->RSSetViewports(1, viewport);
			}
		}
		*/
		/*auto use_d3dDevice =
			g_graphicsEngine->GetD3DDeviceContext();

		auto& use_mainrendertarget =
			g_graphicsEngine->GetMainRenderTarget();

		auto use_framebufferviewports =
			g_graphicsEngine->GetFrameBufferViewports();

		ID3D11RenderTargetView* rtTbl[] = {
			use_mainrendertarget.GetRenderTargetView()
		};
		//レンダリングターゲットの切り替え。
		use_d3dDevice->OMSetRenderTargets(1, rtTbl, use_mainrendertarget.GetDepthStensilView());
		if (&use_framebufferviewports != nullptr) {
			//ビューポートが指定されていたら、ビューポートも変更する。
			use_d3dDevice->RSSetViewports(1, &use_framebufferviewports);
		}
		float clearcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		use_mainrendertarget.ClearRenderTarget(clearcolor);

		////2Dを描く。
		m_copyMainRtToFrameBufferSprite.Draw();*/




		/*
		auto d3dDevice = g_graphicsEngine->GetD3DDeviceContext();
			d3dDevice->OMSetRenderTargets
			(
				1,
				g_graphicsEngine->GetBackBuffer(),
				g_graphicsEngine->GetRenderTarget().GetDepthStensilView()
			);
		*/

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
// todo	void mtGameObjectManager::ExecuteFromDrawThread()
//{
//	//描画処理
//	//Draw();
//}
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
