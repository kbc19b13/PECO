#include "stdafx.h"
#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine()
{
}


GraphicsEngine::~GraphicsEngine()
{
	Release();
}

void GraphicsEngine::BegineRender()
{

	//深度ステンシルバッファを設定する	
	m_pd3dDeviceContext->OMSetRenderTargets(1, &m_backBuffer, m_renderTarget.GetDepthStensilView());
	float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; //red,green,blue,alpha

	m_pd3dDeviceContext->ClearRenderTargetView(m_backBuffer, ClearColor);

	ID3D11RenderTargetView* oldRenderTargetView;
	ID3D11DepthStencilView* oldDepthStencilView;
	m_pd3dDeviceContext->OMGetRenderTargets(1, &oldRenderTargetView, &oldDepthStencilView);
	//レンダリングターゲットを切り替える。
	ID3D11RenderTargetView* rts[] = {
		m_renderTarget.GetRenderTargetView()	//｛　配列を挟まないといけない！！！！　｝
	};
	m_pd3dDeviceContext->OMSetRenderTargets(
		1,									//レンダリングターゲットも数
		rts,								//レンダリングターゲットビューを指定
		m_renderTarget.GetDepthStensilView()//デプスステンシルビューも指定
	);										//描き込み先をバックバッファにする。

	//ビューポートもバックアップを取っておく。
	unsigned int numViewport = 1;
	D3D11_VIEWPORT oldViewports;
	m_pd3dDeviceContext->RSGetViewports(&numViewport, &oldViewports);
								
	//バックバッファを灰色で塗りつぶす。
	m_renderTarget.ClearRenderTarget(ClearColor);

	//シャドウマップにレンダリング
	m_shadowMap.RenderToShadowMap();

	//レンダリングターゲットを元に戻す。
	m_pd3dDeviceContext->OMSetRenderTargets(1, &oldRenderTargetView, oldDepthStencilView);
	
	m_pd3dDeviceContext->RSSetViewports(numViewport, &oldViewports);
	
	//レンダリングターゲットとデプスステンシルの参照カウンタを下す。
	oldRenderTargetView->Release();
	oldDepthStencilView->Release();
}
void GraphicsEngine::EndRender()
{
	//バックバッファとフロントバッファを入れ替える。
	m_pSwapChain->Present(2, 0);
}
void GraphicsEngine::Release()
{
	if (m_rasterizerState != NULL) {
		m_rasterizerState->Release();
		m_rasterizerState = NULL;
	}
	if (m_depthStencil != NULL) {
		m_depthStencil->Release();
		m_depthStencil = NULL;
	}
	if (m_backBuffer != NULL) {
		m_backBuffer->Release();
		m_backBuffer = NULL;
	}
	if (m_pSwapChain != NULL) {
		m_pSwapChain->Release();
		m_pSwapChain = NULL;
	}
	if (m_pd3dDeviceContext != NULL) {
		m_pd3dDeviceContext->Release();
		m_pd3dDeviceContext = NULL;
	}
	if (m_pd3dDevice != NULL) {
		m_pd3dDevice->Release();
		m_pd3dDevice = NULL;
	}
}
void GraphicsEngine::Init(HWND hWnd)
{
	//スワップチェインを作成するための情報を設定する。
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;									//スワップチェインのバッファ数。通常は１。
	sd.BufferDesc.Width = (UINT)FRAME_BUFFER_W;			//フレームバッファの幅。
	sd.BufferDesc.Height = (UINT)FRAME_BUFFER_H;		//フレームバッファの高さ。
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//フレームバッファのフォーマット。R8G8B8A8の32bit。
	sd.BufferDesc.RefreshRate.Numerator = 60;			//モニタのリフレッシュレート。(バックバッファとフロントバッファを入れ替えるタイミングとなる。)
	sd.BufferDesc.RefreshRate.Denominator = 1;			//２にしたら30fpsになる。1でいい。
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//サーフェスまたはリソースを出力レンダー ターゲットとして使用します。
	sd.OutputWindow = hWnd;								//出力先のウィンドウハンドル。
	sd.SampleDesc.Count = 1;							//1でいい。
	sd.SampleDesc.Quality = 0;							//MSAAなし。0でいい。
	sd.Windowed = TRUE;									//ウィンドウモード。TRUEでよい。

														//利用するDirectXの機能セット。DirectX10以上に対応しているGPUを利用可能とする。
														//この配列はD3D11CreateDeviceAndSwapChainの引数として使う。
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	//D3Dデバイスとスワップチェインを作成する。
	D3D11CreateDeviceAndSwapChain(
		NULL,											//NULLでいい。
		D3D_DRIVER_TYPE_HARDWARE,						//D3Dデバイスがアクセスするドライバーの種類。
														//基本的にD3D_DRIVER_TYPE_HARDWAREを指定すればよい。
		NULL,											//NULLでいい。
		0,												//０でいい。
		featureLevels,									//D3Dデバイスのターゲットとなる機能セットを指定する。
														//今回のサンプルはDirectX10以上をサポートするので、
														//それらを含むD3D_FEATURE_LEVELの配列を渡す。
		sizeof(featureLevels) / sizeof(featureLevels[0]),	//機能セットの数。
		D3D11_SDK_VERSION,								//使用するDirectXのバージョン。
														//D3D11_SDK_VERSIONを指定すればよい。
		&sd,											//スワップチェインを作成するための情報。
		&m_pSwapChain,									//作成したスワップチェインのアドレスの格納先。
		&m_pd3dDevice,									//作成したD3Dデバイスのアドレスの格納先。
		&m_featureLevel,								//使用される機能セットの格納先。
		&m_pd3dDeviceContext							//作成したD3Dデバイスコンテキストのアドレスの格納先。
	);
	m_shadowMap.Init();
	m_renderTarget.Create((UINT)FRAME_BUFFER_W, (UINT)FRAME_BUFFER_H, DXGI_FORMAT_R8G8B8A8_UNORM/*DXGI_FORMAT_D32_FLOAT*/);


	//書き込み先になるレンダリングターゲットを作成。
	ID3D11Texture2D* pBackBuffer = NULL;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_backBuffer);
	pBackBuffer->Release();


	//Chaptre9のGame.cpp
	
	//深度テクスチャの作成。
	D3D11_TEXTURE2D_DESC texDesc;
		
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	//ラスタライザとビューポートを初期化。
	m_pd3dDevice->CreateRasterizerState(&desc, &m_rasterizerState);

	D3D11_VIEWPORT viewport;
	viewport.Width = FRAME_BUFFER_W;
	viewport.Height = FRAME_BUFFER_H;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_pd3dDeviceContext->RSSetViewports(1, &viewport);
	m_pd3dDeviceContext->RSSetState(m_rasterizerState);
}
