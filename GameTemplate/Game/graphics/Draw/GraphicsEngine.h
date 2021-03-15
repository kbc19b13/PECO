#pragma once
#include "RenderTarget.h"
#include "graphics/Draw/ShadowMap.h"
#include "Sprite.h"

/// <summary>
/// レンダリングモード
/// </summary>
enum EnRenderMode
{
	enRenderMode_Normal,		//通常描画
	enRenderMode_Silhouette,	//シルエット描画
	enRenderMode_ShadowMap,		//シャドウマップ描画
};
/*!
 *@brief	グラフィックスエンジン。
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	初期化。
	 *@param[in]	hWnd		ウィンドウハンドル。
	 */
	void Init(HWND hWnd);
	/// <summary>
	/// エフェクサーの初期化
	/// </summary>
	void InitEffekseer();
	/*!
	 *@brief	解放。
	 */
	void Release();
	/*!
	 *@brief	D3D11デバイスを取得。
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11デバイスコンテキストを取得。
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	描画開始。
	 */
	void BegineRender();

	/// <summary>
	/// 事前レンダリング
	/// </summary>
	void PreRender();
	/// <summary>
	/// メインレンダリング
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// ポストエフェクトレンダリング
	/// </summary>
	void PostRender();

	/*!
	 *@brief	描画終了。
	 */
	void EndRender();
	void GraphicsEngine::ChangeRenderTarget(RenderTarget* renderTarget, D3D11_VIEWPORT* viewport)
	{
		ChangeRenderTarget(
			renderTarget->GetRenderTargetView(),
			renderTarget->GetDepthStensilView(),
			viewport
		);
	}
	void GraphicsEngine::ChangeRenderTarget(ID3D11RenderTargetView* renderTarget, ID3D11DepthStencilView* depthStensil, D3D11_VIEWPORT* viewport)
	{
		ID3D11RenderTargetView* rtTbl[] = {
			renderTarget
		};
		//レンダリングターゲットの切り替え。
		m_pd3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
		if (viewport != nullptr) {
			//ビューポートが指定されていたら、ビューポートも変更する。
			m_pd3dDeviceContext->RSSetViewports(1, viewport);
		}
		/*
		ID3D11RenderTargetView* rt[] = {
		m_3dObjectRenderTarget.GetRenderTargetView()
	};
	m_pd3dDeviceContext->OMSetRenderTargets(
		1,
		rt,
		m_3dObjectRenderTarget.GetDepthStensilView()
	);
	//ビューポートを設定。
	m_pd3dDeviceContext->RSSetViewports(1, m_3dObjectRenderTarget.GetViewport());
		*/
	}
	/// <summary>
	/// シャドウマップを取得。
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}

	/// <summary>
	/// レンダーターゲットビューの取得
	/// </summary>
	/// <returns></returns>
	ID3D11RenderTargetView* GetBackBuffer()
	{
		return m_backBuffer;
	}

	/// <summary>
	/// 3Dオブジェクトのレンダーターゲットを取得
	/// </summary>
	/// <returns></returns>
	RenderTarget& Get3DObjectRenderTarget()
	{
		return m_3dObjectRenderTarget;
	}

	/// <summary>
	/// メンバレンダーターゲットを取得
	/// </summary>
	/// <returns></returns>
	RenderTarget& GetRenderTarget()
	{
		return m_renderTarget;
	}

	D3D11_VIEWPORT& GetFrameBufferViewports()
	{
		return m_frameBufferViewports;
	}

private:
	D3D_FEATURE_LEVEL		m_featureLevel;					//Direct3D デバイスのターゲットとなる機能セット。
	ID3D11Device*			m_pd3dDevice = NULL;			//D3D11デバイス。
	IDXGISwapChain*			m_pSwapChain = NULL;			//スワップチェイン。
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;		//D3D11デバイスコンテキスト。
	ID3D11RenderTargetView* m_backBuffer = NULL;			//バックバッファ。
	ID3D11RasterizerState*	m_rasterizerState = NULL;		//ラスタライザステート。
	ID3D11Texture2D*		m_depthStencil = nullptr;		//デプスステンシルとなるテクスチャ。
	ID3D11DepthStencilView* m_depthStencilView = nullptr;	//!<デプスステンシルビュー。

	ShadowMap m_shadowMap;									//シャドウマップ。

															//レンダリングターゲット関係のメンバ変数です。
	//レンダリングターゲットの改造を楽にするために作成
	RenderTarget m_renderTarget;							//todo レンダリングターゲット

	RenderTarget m_3dObjectRenderTarget;					//todo 3Dオブジェクトをレンダリングするためのレンダリングターゲット。
	Sprite m_copy3dObjectRtToFrameBufferSprite;				//todo 3Dオブジェクトが描かれたテクスチャをフレームバッファにコピーするためのスプライト。

	//Effekseerマネージャ管理。
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;
	
	D3D11_VIEWPORT m_frameBufferViewports;					//フレームバッファのビューポート。

	ID3D11RenderTargetView* oldRenderTargetView = nullptr;	//フレームバッファのレンダリングターゲットビュー。
	ID3D11DepthStencilView* oldDepthStencilView = nullptr;	//フレームバッファのデプスステンシルビュー。

};

extern GraphicsEngine* g_graphicsEngine;				//グラフィックスエンジン