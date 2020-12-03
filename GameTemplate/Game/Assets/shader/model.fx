/*!
 * @brief	モデルシェーダー。
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//アルベドテクスチャ。
Texture2D<float4> albedoTexture : register(t0);	
//ボーン行列
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// 定数バッファ。
/////////////////////////////////////////////////////////////
/*!
 * @brief	頂点シェーダーとピクセルシェーダー用の定数バッファ。
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

static const int Number_Direcyion_Light = 4;

/// <summary>
/// ライト用の定数バッファ。
/// </summary>
struct SDirectionLight {
	float3 direction[Number_Direcyion_Light]; //→
		//float ...; →が勝手に追加されている
	float4 color[Number_Direcyion_Light];
	};

/// <summary>
/// ライト用の定数バッファ
/// </summary>
cbuffer LightCb : register(b0) {
	SDirectionLight		directionLight;		//ディレクションライト。
	float3				eyePos;				//カメラの視点。
	float				specPow;			//スペキュラライトの絞り。
};


/////////////////////////////////////////////////////////////
//各種構造体
/////////////////////////////////////////////////////////////
/*!
 * @brief	スキンなしモデルの頂点構造体。
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float3 Tangent  : TANGENT;				//接ベクトル。
    float2 TexCoord : TEXCOORD0;			//UV座標。
};
/*!
 * @brief	スキンありモデルの頂点構造体。
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//頂点座標。
    float3 Normal   : NORMAL;				//法線。
    float2 TexCoord	: TEXCOORD0;			//UV座標。
    float3 Tangent	: TANGENT;				//接ベクトル。
    uint4  Indices  : BLENDINDICES0;		//この頂点に関連付けされているボーン番号。x,y,z,wの要素に入っている。4ボーンスキニング。
    float4 Weights  : BLENDWEIGHT0;			//この頂点に関連付けされているボーンへのスキンウェイト。x,y,z,wの要素に入っている。4ボーンスキニング。
};

/*!
 * @brief	ピクセルシェーダーの入力。
 */
struct PSInput{
	float4 Position 	: SV_POSITION;	//座標
	float3 Normal		: NORMAL;		//法線
	float3 Tangent		: TANGENT;		//ターゲット
	float3 worldPos		: TEXCOORD1;	//ワールド座標
	float2 TexCoord 	: TEXCOORD0;	//UV座標
};
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	//ワールド座標をピクセルシェーダーに渡す。
	psInput.worldPos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	//UV座標はそのままピクセルシェーダーに渡す。
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	//法線はそのままピクセルシェーダーに渡す。
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
 * 全ての頂点に対してこのシェーダーが呼ばれる。
 * Inは1つの頂点データ。VSInputNmTxWeightsを見てみよう。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//ここからスキニングを行っている箇所。
	//スキン行列を計算。
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrixにボーン行列が設定されていて、
			//In.indicesは頂点に埋め込まれた、関連しているボーンの番号。
			//In.weightsは頂点に埋め込まれた、関連しているボーンのウェイト。
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //最後のボーンを計算する。
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//頂点座標にスキン行列を乗算して、頂点をワールド空間に変換。
		//mulは乗算命令。
	    pos = mul(skinning, In.Position);
		//ワールド座標をピクセルシェーダーに渡す。
		psInput.worldPos = pos;
	}
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;

    return psInput;
}

//--------------------------------------------------------------------------------------
// シルエット描画用のピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain_Silhouette(PSInput In) : SV_Target0
{
	return float4(0.5f, 0.5f, 0.5f, 1.0f);
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{

	//albedoテクスチャからカラーをフェッチする。
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//ディレクションライトの拡散反射光を計算する。
	float3 lig = 0.0f;
	for (int i = 0; i < Number_Direcyion_Light; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i];
	
	//ディレクションライトの鏡面反射光を計算する。
	{
		//実習　鏡面反射を計算しなさい。
		//�@ ライトを当てる面から視点に伸びるベクトルtoEyeDirを求める。
		//	 視点の座標は定数バッファで渡されている。LightCbを参照するように。
		float3 toEyeDir = eyePos - In.worldPos;
		toEyeDir = normalize(toEyeDir);

		//�A １で求めたtoEyeDirの反射ベクトルを求める。
		float3 R = reflect(
			directionLight.direction[i],
			In.Normal
		);

		//�B ２で求めた反射ベクトルとディレクションライトの方向との内積を取って、スペキュラの強さを計算する。
		float t = dot(R, toEyeDir);
		//内積の結果でマイナスが返ってこないようにする。
		if (t < 0.0f) {
			t = 0.0f;
		}

		//�C pow関数を使って、スペキュラを絞る。絞りの強さは定数バッファで渡されている。
		//	 LightCbを参照するように。
		t = pow(t, specPow);

		//�D 鏡面反射が求まったら、ligに加算する。
		//鏡面反射を反射光に加算する。
		lig += directionLight.color[i].xyz * t;

	}
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);											//   ×
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
	//return albedoTexture.Sample(Sampler, In.TexCoord);//finalColor
}

