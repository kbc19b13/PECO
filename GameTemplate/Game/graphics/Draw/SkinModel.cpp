#include "stdafx.h"
#include "graphics/Draw/SkinModel.h"
#include "graphics/SkinModelDataManager.h"
#include "graphics/Draw/SkinModelEffect.h"

SkinModel::~SkinModel()
{
	if (m_cb != nullptr) {
		//定数バッファを解放。
		m_cb->Release();
	}
	if (m_samplerState != nullptr) {
		//サンプラステートを解放。
		m_samplerState->Release();
	}
	/// <summary>
	/// ライト用の定数バッファの解放。
	/// </summary>
	if (m_lightCb != nullptr) {
		m_lightCb->Release();
	}
	
}
void SkinModel::Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis)
{
	

	//スケルトンのデータを読み込む。
	InitSkeleton(filePath);

	//定数バッファの作成。
	InitConstantBuffer();

	//サンプラステートの初期化。
	InitSamplerState();

	/// <summary>
	/// ディレクションライトの初期化。
	/// </summary>
	InitDirectionLight();

	//SkinModelDataManagerを使用してCMOファイルのロード。
	m_modelDx = g_skinModelDataManager.Load(filePath, m_skeleton);

	m_enFbxUpAxis = enFbxUpAxis;
}
void SkinModel::InitSkeleton(const wchar_t* filePath)
{
	//スケルトンのデータを読み込む。
	//cmoファイルの拡張子をtksに変更する。
	std::wstring skeletonFilePath = filePath;
	//文字列から.cmoファイル始まる場所を検索。
	int pos = (int)skeletonFilePath.find(L".cmo");
	//.cmoファイルを.tksに置き換える。
	skeletonFilePath.replace(pos, 4, L".tks");
	//tksファイルをロードする。
	bool result = m_skeleton.Load(skeletonFilePath.c_str());
	if ( result == false ) {
		//スケルトンが読み込みに失敗した。
		//アニメーションしないモデルは、スケルトンが不要なので
		//読み込みに失敗することはあるので、ログ出力だけにしておく。
#ifdef _DEBUG
		char message[256];
		sprintf(message, "tksファイルの読み込みに失敗しました。%ls\n", skeletonFilePath.c_str());
		OutputDebugStringA(message);
#endif
	}
}
void SkinModel::InitConstantBuffer()
{
	//作成するバッファのサイズをsizeof演算子で求める。
	int bufferSize = sizeof(SVSConstantBuffer);
	//どんなバッファを作成するのかをせてbufferDescに設定する。
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));				//０でクリア。
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファで想定されている、読み込みおよび書き込み方法。
	bufferDesc.ByteWidth = Raundup16(bufferSize);				//バッファは16バイトアライメントになっている必要がある。
																//アライメントって→バッファのサイズが16の倍数ということです。
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;			//バッファをどのようなパイプラインにバインドするかを指定する。
																//定数バッファにバインドするので、D3D11_BIND_CONSTANT_BUFFERを指定する。
	bufferDesc.CPUAccessFlags = 0;								//CPU アクセスのフラグです。
																//CPUアクセスが不要な場合は0。
	//作成。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_cb);


	//ライト用の定数バッファを作成。
	//作成するバッファのサイズを変更する
	bufferDesc.ByteWidth = sizeof(SLight);				//SDirectionLightは16byteの倍数になっているので、切り上げはやらない。
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&bufferDesc, NULL, &m_lightCb);


}
void SkinModel::InitSamplerState()
{
	//テクスチャのサンプリング方法を指定するためのサンプラステートを作成。
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}

void SkinModel::InitDirectionLight()
{
	//一本目は太陽光
	m_light.directionLight.direction[0] = { 1.0f, -1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[0].Normalize();
	m_light.directionLight.color[0] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//二本目は地面からの照り返し
	m_light.directionLight.direction[1] = { 1.0f, 1.0f, 0.0f, 0.0f };
	m_light.directionLight.direction[1].Normalize();
	m_light.directionLight.color[1] = { 0.4f, 0.4f, 0.4f, 1.0f };

	//残りは周囲のオブジェクトからの反射光だとする
	m_light.directionLight.direction[2] = { -1.0f, 0.0f, 1.0f, 0.0f };
	m_light.directionLight.direction[2].Normalize();
	m_light.directionLight.color[2] = { 0.3f, 0.3f, 0.3f, 1.0f };

	m_light.directionLight.direction[3] = { 1.0f, 0.0f, -1.0f, 0.0f };
	m_light.directionLight.direction[3].Normalize();
	m_light.directionLight.color[3] = { 0.3f, 0.3f, 0.3f, 1.0f };
	
	m_light.specPow = 2.0f;
}
void SkinModel::UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale)
{
	//3dsMaxと軸を合わせるためのバイアス。
	CMatrix mBias = CMatrix::Identity();
	if (m_enFbxUpAxis == enFbxUpAxisZ) {
		//Z-up
		mBias.MakeRotationX(CMath::PI * -0.5f);
	}
	CMatrix transMatrix, rotMatrix, scaleMatrix;
	//平行移動行列を作成する。
	transMatrix.MakeTranslation( position );
	//回転行列を作成する。
	rotMatrix.MakeRotationFromQuaternion( rotation );
	rotMatrix.Mul(mBias, rotMatrix);
	//拡大行列を作成する。
	scaleMatrix.MakeScaling(scale);
	//ワールド行列を作成する。
	//拡大×回転×平行移動の順番で乗算するように！
	//順番を間違えたら結果が変わるよ。
	m_worldMatrix.Mul(scaleMatrix, rotMatrix);
	m_worldMatrix.Mul(m_worldMatrix, transMatrix);

	//スケルトンの更新。
	m_skeleton.Update(m_worldMatrix);
}
void SkinModel::Draw(CMatrix viewMatrix, CMatrix projMatrix , EnRenderMode rendermode)
{
	ID3D11DeviceContext* d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	DirectX::CommonStates state(g_graphicsEngine->GetD3DDevice());
	
	auto shadowMap = g_graphicsEngine->GetShadowMap();

	//定数バッファを更新。
	SVSConstantBuffer modelFxCb;
	modelFxCb.mWorld = m_worldMatrix;
	modelFxCb.mProj = projMatrix;
	modelFxCb.mView = viewMatrix;
	//ライトカメラのビュー、プロジェクション行列を送る。
	modelFxCb.mLightProj = shadowMap->GetLightProjMatrix();
	modelFxCb.mLightView = shadowMap->GetLighViewMatrix();
	if (m_isShadowReciever == true) {
		modelFxCb.isShadowReciever = 1;
	}
	else {
		modelFxCb.isShadowReciever = 0;
	}


	d3dDeviceContext->UpdateSubresource(m_cb, 0, nullptr, &modelFxCb, 0, 0);
	//視点を設定。
	m_light.eyePos = g_camera3D.GetPosition();
	//ライト用の定数バッファを更新。
	d3dDeviceContext->UpdateSubresource(m_lightCb, 0, nullptr, &m_light, 0, 0);

	
	//定数バッファをGPUに転送。
	d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_cb);
	d3dDeviceContext->PSSetConstantBuffers(0, 1, &m_cb);

	d3dDeviceContext->PSSetConstantBuffers(1, 1, &m_lightCb);
	//サンプラステートを設定。
	d3dDeviceContext->PSSetSamplers(0, 1, &m_samplerState);
	ID3D11ShaderResourceView* srv = shadowMap->GetShdowMapTexture();
	d3dDeviceContext->PSSetShaderResources(2, 1, &srv);

	//ボーン行列をGPUに転送。
	m_skeleton.SendBoneMatrixArrayToGPU();

	m_modelDx->UpdateEffects([&](DirectX::IEffect* material) {
		auto modelMaterial = reinterpret_cast<ModelEffect*>(material);
		modelMaterial->SetRenderMode(rendermode);
		});

	//描画。
	m_modelDx->Draw(
		d3dDeviceContext,
		state,
		m_worldMatrix,
		viewMatrix,
		projMatrix
	);
}