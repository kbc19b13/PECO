/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
 */

cbuffer cb : register(b0) {
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float alpha;		//���l�B
};
struct VSInput {
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
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
	//�e�N�X�`���J���[�����̂܂ܕԂ��B
	float4 color = colorTexture.Sample(Sampler, In.uv);
	//color�̌^��float4��1�e�N�Z���̃J���[��񂪓����Ă���
	float Y = 0.29900 * color.x + 0.58700 * color.z + 0.11400 * color.z;
	//���m�N����
	/*
	color.x = Y;
	color.y = Y;
	color.z = Y;
	*/

	//�R���g���X�g�����߂�
	//������1�s�N�Z�������R���g���X�g�����߂�T���v���R�[�h
	//�܂��A�s�N�Z���̖��x�����߂�B
	/*
	float Brightness = max(color.x, color.y);
	Brightness = max(Brightness, color.z);
	if (Brightness > 0.5f)
	{
		//���邳��0.5�ȏ�Ȃ�A����ɖ��邭����B
		color.x = min(1.0f, color.x * 1.5f);
		color.y = min(1.0f, color.y * 1.5f);
		color.z = min(1.0f, color.z * 1.5f);
	}
	else
	{
		//���邳��0.5�����Ȃ�A����ɈÂ�����B
		color.x *= 0.5f;
		color.y *= 0.5f;
		color.z *= 0.5f;
	}
	*/
	/*
	//�Z�s�A���ɂ���
	//���m�N����������
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