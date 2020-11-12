/*!
 * @brief	���f���V�F�[�_�[�B
 */


/////////////////////////////////////////////////////////////
// Shader Resource View
/////////////////////////////////////////////////////////////
//�A���x�h�e�N�X�`���B
Texture2D<float4> albedoTexture : register(t0);	
//�{�[���s��
StructuredBuffer<float4x4> boneMatrix : register(t1);

/////////////////////////////////////////////////////////////
// SamplerState
/////////////////////////////////////////////////////////////
sampler Sampler : register(s0);

/////////////////////////////////////////////////////////////
// �萔�o�b�t�@�B
/////////////////////////////////////////////////////////////
/*!
 * @brief	���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�B
 */
cbuffer VSPSCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};

static const int Number_Direcyion_Light = 4;

/// <summary>
/// ���C�g�p�̒萔�o�b�t�@�B
/// </summary>
struct SDirectionLight {
	float3 direction[Number_Direcyion_Light]; //��
		//float ...; ��������ɒǉ�����Ă���
	float4 color[Number_Direcyion_Light];
	};

/// <summary>
/// ���C�g�p�̒萔�o�b�t�@
/// </summary>
cbuffer LightCb : register(b0) {
	SDirectionLight		directionLight;		//�f�B���N�V�������C�g�B
	float3				eyePos;				//�J�����̎��_�B
	float				specPow;			//�X�y�L�������C�g�̍i��B
};


/////////////////////////////////////////////////////////////
//�e��\����
/////////////////////////////////////////////////////////////
/*!
 * @brief	�X�L���Ȃ����f���̒��_�\���́B
 */
struct VSInputNmTxVcTangent
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float3 Tangent  : TANGENT;				//�ڃx�N�g���B
    float2 TexCoord : TEXCOORD0;			//UV���W�B
};
/*!
 * @brief	�X�L�����胂�f���̒��_�\���́B
 */
struct VSInputNmTxWeights
{
    float4 Position : SV_Position;			//���_���W�B
    float3 Normal   : NORMAL;				//�@���B
    float2 TexCoord	: TEXCOORD0;			//UV���W�B
    float3 Tangent	: TANGENT;				//�ڃx�N�g���B
    uint4  Indices  : BLENDINDICES0;		//���̒��_�Ɋ֘A�t������Ă���{�[���ԍ��Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
    float4 Weights  : BLENDWEIGHT0;			//���̒��_�Ɋ֘A�t������Ă���{�[���ւ̃X�L���E�F�C�g�Bx,y,z,w�̗v�f�ɓ����Ă���B4�{�[���X�L�j���O�B
};

/*!
 * @brief	�s�N�Z���V�F�[�_�[�̓��́B
 */
struct PSInput{
	float4 Position 	: SV_POSITION;	//���W
	float3 Normal		: NORMAL;		//�@��
	float3 Tangent		: TANGENT;		//�^�[�Q�b�g
	float3 worldPos		: TEXCOORD1;	//���[���h���W
	float2 TexCoord 	: TEXCOORD0;	//UV���W
};
/*!
 *@brief	�X�L���s����v�Z�B
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
 * @brief	�X�L���Ȃ����f���p�̒��_�V�F�[�_�[�B
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(mWorld, In.Position);
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	//UV���W�͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.Normal = normalize(mul(mWorld, In.Normal));
	//�@���͂��̂܂܃s�N�Z���V�F�[�_�[�ɓn���B
	psInput.Tangent = normalize(mul(mWorld, In.Tangent));
	return psInput;
}

/*!--------------------------------------------------------------------------------------
 * @brief	�X�L�����胂�f���p�̒��_�V�F�[�_�[�B
 * �S�Ă̒��_�ɑ΂��Ă��̃V�F�[�_�[���Ă΂��B
 * In��1�̒��_�f�[�^�BVSInputNmTxWeights�����Ă݂悤�B
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	///////////////////////////////////////////////////
	//��������X�L�j���O���s���Ă���ӏ��B
	//�X�L���s����v�Z�B
	///////////////////////////////////////////////////
	float4x4 skinning = 0;	
	float4 pos = 0;
	{
	
		float w = 0.0f;
	    for (int i = 0; i < 3; i++)
	    {
			//boneMatrix�Ƀ{�[���s�񂪐ݒ肳��Ă��āA
			//In.indices�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̔ԍ��B
			//In.weights�͒��_�ɖ��ߍ��܂ꂽ�A�֘A���Ă���{�[���̃E�F�C�g�B
	        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
	        w += In.Weights[i];
	    }
	    //�Ō�̃{�[�����v�Z����B
	    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
	  	//���_���W�ɃX�L���s�����Z���āA���_�����[���h��Ԃɕϊ��B
		//mul�͏�Z���߁B
	    pos = mul(skinning, In.Position);
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
// �s�N�Z���V�F�[�_�[�̃G���g���֐��B
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{

	//albedo�e�N�X�`������J���[���t�F�b�`����B
	float4 albedoColor = albedoTexture.Sample(Sampler, In.TexCoord);
	//�f�B���N�V�������C�g�̊g�U���ˌ����v�Z����B
	float3 lig = 0.0f;
	for (int i = 0; i < Number_Direcyion_Light; i++) {
		lig += max(0.0f, dot(In.Normal * -1.0f, directionLight.direction[i])) * directionLight.color[i];
	
	//�f�B���N�V�������C�g�̋��ʔ��ˌ����v�Z����B
	{
		//���K�@���ʔ��˂��v�Z���Ȃ����B
		//�@ ���C�g�𓖂Ă�ʂ��王�_�ɐL�т�x�N�g��toEyeDir�����߂�B
		//	 ���_�̍��W�͒萔�o�b�t�@�œn����Ă���BLightCb���Q�Ƃ���悤�ɁB
		float3 toEyeDir = eyePos - In.worldPos;
		toEyeDir = normalize(toEyeDir);

		//�A �P�ŋ��߂�toEyeDir�̔��˃x�N�g�������߂�B
		float3 R = reflect(
			directionLight.direction[i],
			In.Normal
		);

		//�B �Q�ŋ��߂����˃x�N�g���ƃf�B���N�V�������C�g�̕����Ƃ̓��ς�����āA�X�y�L�����̋������v�Z����B
		float t = dot(R, toEyeDir);
		//���ς̌��ʂŃ}�C�i�X���Ԃ��Ă��Ȃ��悤�ɂ���B
		if (t < 0.0f) {
			t = 0.0f;
		}

		//�C pow�֐����g���āA�X�y�L�������i��B�i��̋����͒萔�o�b�t�@�œn����Ă���B
		//	 LightCb���Q�Ƃ���悤�ɁB
		t = pow(t, specPow);

		//�D ���ʔ��˂����܂�����Alig�ɉ��Z����B
		//���ʔ��˂𔽎ˌ��ɉ��Z����B
		lig += directionLight.color[i].xyz * t;

	}
	}
	float4 finalColor = float4(0.0f, 0.0f, 0.0f, 1.0f);											//   �~
	finalColor.xyz = albedoColor.xyz * lig;
	return finalColor;
	//return albedoTexture.Sample(Sampler, In.TexCoord);//finalColor
}