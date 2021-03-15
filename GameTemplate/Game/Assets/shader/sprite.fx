/*!
 * @brief	スプライト用のシェーダー。
 */

cbuffer cb : register(b0) {
	float4x4 mvp;		//ワールドビュープロジェクション行列。
	float alpha;		//α値。
};
struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
	PSInput psIn;
	psIn.pos = mul(mvp, In.pos);
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
	//テクスチャカラーをそのまま返す。
	float4 color = colorTexture.Sample(Sampler, In.uv);
	//colorの型はfloat4で1テクセルのカラー情報が入っている
	float Y = 0.29900 * color.x + 0.58700 * color.z + 0.11400 * color.z;
	//モノクロ化
	/*
	color.x = Y;
	color.y = Y;
	color.z = Y;
	*/

	//コントラストを強める
	//左下の1ピクセルだけコントラストを強めるサンプルコード
	//まず、ピクセルの明度を求める。
	/*
	float Brightness = max(color.x, color.y);
	Brightness = max(Brightness, color.z);
	if (Brightness > 0.5f)
	{
		//明るさが0.5以上なら、さらに明るくする。
		color.x = min(1.0f, color.x * 1.5f);
		color.y = min(1.0f, color.y * 1.5f);
		color.z = min(1.0f, color.z * 1.5f);
	}
	else
	{
		//明るさが0.5未満なら、さらに暗くする。
		color.x *= 0.5f;
		color.y *= 0.5f;
		color.z *= 0.5f;
	}
	*/
	/*
	//セピア調にする
	//モノクロ化もいる
	color.x *= 1.07;
	color.y *= 0.74;
	color.z *= 0.43;
	*/
	/*
	color.x *= color.x / 765 * 100;
	color.y *= color.y / 765 * 100;
	color.z *= color.z / 765 * 100;
	*/

	return color;
}