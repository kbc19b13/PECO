#include "stdafx.h"
#include "graphics/Draw/SkinModelEffect.h"
#include "graphics/SkinModelShaderConst.h"

ModelEffect::ModelEffect()
{
	//���_�V�F�[�_�[�����[�h
	m_psShader.Load("Assets/shader/model.fx", "PSMain", Shader::EnType::PS);
	m_pPSShader = &m_psShader;
	m_psSilhouette.Load("Assets/shader/model.fx", "PSMain_Silhouette", Shader::EnType::PS);
	m_pPSSilhouette = &m_psSilhouette;

	//�V���h�E�}�b�v�p�̃V�F�[�_�[�����[�h
	m_psShadowMap.Load("Assets/shader/model.fx", "PSMain_ShadowMap", Shader::EnType::PS);
	m_pPSShadowMap = &m_psShadowMap;
	m_vsShadowMap.Load("Assets/shader/model.fx", "VSMain_ShadowMap", Shader::EnType::VS);
	m_pVSShadowMap = &m_vsShadowMap;

	InitSilhouettoDepthStepsilState();
}

void ModelEffect::InitSilhouettoDepthStepsilState()
{
	//D3D�f�o�C�X���擾�B
	auto pd3d = g_graphicsEngine->GetD3DDevice();
	//�쐬����[�x�X�e���V���X�e�[�g�̒�`��ݒ肵�Ă����B
	D3D11_DEPTH_STENCIL_DESC desc = { 0 };
	desc.DepthEnable = true;						   //Z�e�X�g���L���B
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; //Z�o�b�t�@��Z�l��`�����܂Ȃ��B
	desc.DepthFunc = D3D11_COMPARISON_GREATER;		   //Z�l���傫����΃t���[���o�b�t�@�ɕ`�����ށB

	pd3d->CreateDepthStencilState(&desc, &m_silhouettoDepthStepsilState);

	//�f�v�X�X�e���V���X�e�[�g���쐬�B
	pd3d->CreateDepthStencilState(&desc, &depthStencilState);
}

void __cdecl ModelEffect::Apply(ID3D11DeviceContext* deviceContext)
{
	
	//�`��̐؂�ւ�
	switch (m_renderMode) {
	case enRenderMode_Normal:
		//�ʏ�`��B
		//�V�F�[�_�[��K������
		deviceContext->VSSetShader((ID3D11VertexShader*)m_pVSShader->GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSShader->GetBody(), NULL, 0);
		
		//�G���[�R�[�hC2360���ł��̂�{}��ǉ�
		{
			//�V�F�[�_�[���\�[�X�r���[����C�ɐݒ肷��B
			ID3D11ShaderResourceView* srvArray[] = {
				m_albedoTex,											//�A���x�h�e�N�X�`���B
				g_graphicsEngine->GetShadowMap()->GetShdowMapTexture()	//�V���h�E�}�b�v�B
			};
		}

		//deviceContext->PSSetShaderResources(0, 2, srvArray);
		deviceContext->PSSetShaderResources(enSkinModelSRVReg_AlbedoTexture, 1, &m_albedoTex);
		
		break;
	case enRenderMode_Silhouette:
		//�V���G�b�g�`��
		deviceContext->PSSetShader((ID3D11PixelShader*)m_pPSSilhouette->GetBody(), NULL, 0);
		//�f�v�X�X�e���V���X�e�[�g��؂�ւ���
		deviceContext->OMSetDepthStencilState(m_silhouettoDepthStepsilState, 0);
		break;
	case enRenderMode_ShadowMap:
		//�V���h�E�}�b�v�����p�̃V�F�[�_�[��ݒ�B
		//�V���h�E�}�b�v�����B
		deviceContext->VSSetShader((ID3D11VertexShader*)m_vsShadowMap.GetBody(), NULL, 0);
		deviceContext->PSSetShader((ID3D11PixelShader*)m_psShadowMap.GetBody(), NULL, 0);
		break;
	}
}