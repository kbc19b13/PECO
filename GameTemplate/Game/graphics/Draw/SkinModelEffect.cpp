#include "stdafx.h"
#include "graphics/Draw/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	//頂点シェーダーをロード
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_pPSShader = &m_psShader;
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	m_pPSSilhouette = &m_psSilhouette;

	//シャドウマップ用のシェーダーをロード
	m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
	m_pPSShadowMap = &m_psShadowMap;
	m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
	m_pVSShadowMap = &m_vsShadowMap;

	InitSilhouettoDepthStepsilState();
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3Dデバイスを取得。
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//作成する深度ステンシルステートの定義を設定していく。
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Zテストが有効。
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //ZバッファにZ値を描き込まない。
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z値が大きければフレームバッファに描き込む。

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);

	//デプスステンシルステートを作成。
	pd3d->CreateDepthStencilState(&desc, &depthStencilState);
}

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	
	//描画の切り替え
	switch (m_renderMode) {
	case enRenderMode_Normal:
		//通常描画。
		//シェーダーを適応する
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		
		//エラーコードC2360がでたので{}を追加
		{
			//シェーダーリソースビューを一気に設定する。
			ID3D11ShaderResourceView* srvArray[] = {
				m_albedoTex,											//アルベドテクスチャ。
				g_graphicsEngine->GetShadowMap()->GetShdowMapTexture()	//シャドウマップ。
			};
		}

		//deviceContext->PSSetShaderResources(0, 2, srvArray);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		
		break;
	case enRenderMode_Silhouette:
		//シルエット描画
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSSilhouette->GetBody(), NULL, 0);
		//デプスステンシルステートを切り替える
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case enRenderMode_ShadowMap:
		//シャドウマップ生成用のシェーダーを設定。
		//シャドウマップ生成。
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}