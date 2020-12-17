#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget()
{

}

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Release()
{
	if (m_depthStencilView != nullptr) {
		m_depthStencilView->Release();
		m_depthStencilView = nullptr;
	}
	if (m_depthStencilTex != nullptr) {
		m_depthStencilTex->Release();
		m_depthStencilTex = nullptr;
	}

	if (m_renderTargetView != nullptr) {
		m_renderTargetView->Release();
		m_renderTargetView = nullptr;
	}
	if (m_renderTargetTex != nullptr) {
		m_renderTargetTex->Release();
		m_renderTargetTex = nullptr;
	}
	if (m_renderTargetSRV != nullptr) {
		m_renderTargetSRV->Release();
	}
}

void RenderTarget::Create(unsigned int w, unsigned int h, DXGI_FORMAT texFormat)
{
	//D3D�f�o�C�X���擾�B
	auto d3dDevice = g_graphicsEngine->GetD3DDevice();
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();
	//1.�����_�����O�^�[�Q�b�g�ƂȂ�e�N�X�`�����쐬�B
	D3D11_TEXTURE2D_DESC texDesc = { 0 };
	{
		//�[�x�X�e���V���r���[�̍쐬�B
		
		//�[�x�e�N�X�`���̍쐬�B

		//�Z�e�N�X�`���̉��̉𑜓x�B
		texDesc.Width = w;
		//�Z�e�N�X�`���̏c�̉𑜓x�B
		texDesc.Height = h;
		//�~�~�b�v�}�b�v���x���B1�ł����B
		texDesc.MipLevels = 1;
		//�Z�e�N�X�`���z��̃T�C�Y�B1�ł����B
		texDesc.ArraySize = 1;
		//�Z�e�N�X�`���̃t�H�[�}�b�g�B
		//�ZRGBA�̊e�v�f8bit��32bit�t�H�[�}�b�g�ɂ���B
		//�Z�I���̃p�����[�^�͍���ύX����̂ŁA���ځI
		texDesc.Format = texFormat;
		//�Z7�e�N�X�`���̎g�p�p�r�����߂�B
		//�Z�����_�����O�^�[�Q�b�g�̃e�N�X�`���́A
		//�������_�����O�^�[�Q�b�g�AShaderResourceView�A
		//�~UnorderedAccessView�Ƃ��ăo�C���h����B
		texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		//texDesc.BindFlags = D3D11_BIND_RENDER_TARGET;
		//�~�}���`�T���v�����O�̐��B1�ł����B
		texDesc.SampleDesc.Count = 1;
		//�~�}���`�T���v�����O�̕i���B0�ł����B
		texDesc.SampleDesc.Quality = 0;
		//�~�e�N�X�`���̓ǂݏ����̂�����BD3D11_USAGE_DEFAULT�ł����B
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		//�~CPU����̃A�N�Z�X�̎d���B�A�N�Z�X���Ȃ��̂�0�ł悢�B
		texDesc.CPUAccessFlags = 0;
		//�~0�ł悢�B
		texDesc.MiscFlags = 0;
		//�Z�e�N�X�`�����쐬�B
		d3dDevice->CreateTexture2D(&texDesc, nullptr, &m_renderTargetTex);
	}
	//2.�����_�����O�^�[�Q�b�g�r���[�̍쐬
	{
		//////////////////////////////////////////////////////////////
		//�������烌���_�����O�^�[�Q�b�g�r���[�̍쐬�B
		//////////////////////////////////////////////////////////////
		//�Z�����_�����O�^�[�Q�b�g�r���[���쐬���邽�߂̃f�[�^��ݒ肷��B�B
		D3D11_RENDER_TARGET_VIEW_DESC viewDesc;
		//�Z�t�H�[�}�b�g�̓e�N�X�`���Ɠ����ɂ���B
		viewDesc.Format = texDesc.Format;
		//�Z2D�e�N�X�`�����������Ƃ��w�肷��B
		viewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		//�~0�ł����B
		viewDesc.Texture2D.MipSlice = 0;
		//�Z�����_�����O�^�[�Q�b�g�r���[�̍쐬�B
		d3dDevice->CreateRenderTargetView(
			m_renderTargetTex,
			&viewDesc,
			&m_renderTargetView
		);
	}
	//3.�V�F�[�_�[���\�[�X�r���[�̍쐬
	{

		//////////////////////////////////////////////////////////////
		//��������V�F�[�_�[���\�[�X�r���[�̍쐬�B
		//////////////////////////////////////////////////////////////

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		//�~�t�H�[�}�b�g�̓e�N�X�`���Ɠ����ł悢�B
		srvDesc.Format = texDesc.Format;
		//�Z2�����e�N�X�`���Ƃ��Ĉ����B
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		//�~�~�b�v�}�b�v���x�����e�N�X�`���Ɠ����ł悢�B
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
		//�~0�ł����B
		srvDesc.Texture2D.MostDetailedMip = 0;
		texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		//�ZSRV���쐬����B
		auto hr = d3dDevice->CreateShaderResourceView(
			m_renderTargetTex,
			&srvDesc,
			&m_renderTargetSRV
		);
		int hog = 0;
	}
	//4.�f�v�X�X�e���V���e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC depthTexDesc = texDesc;
	{
		//////////////////////////////////////////////////////////////
		//��������f�v�X�X�e���V���e�N�X�`���̍쐬�B
		//////////////////////////////////////////////////////////////
		//�Z�f�v�X�X�e���V���r���[�Ƀo�C���h����B
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		//�Z32bit���������_�̃f�v�X�X�e���V���o�b�t�@���쐬����B
		depthTexDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//�Z�f�v�X�X�e���V���e�N�X�`�����쐬����B
		d3dDevice->CreateTexture2D(
			&depthTexDesc,
			nullptr,
			&m_depthStencilTex
		);
	}
	//5.�f�v�X�X�e���V���r���[�̍쐬
	{
		//////////////////////////////////////////////////////////////
		//��������f�v�X�X�e���V���r���[�̍쐬�B
		//////////////////////////////////////////////////////////////
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		//�Z�t�H�[�}�b�g�͐[�x�X�e���V���Ɠ����ɂ���B
		depthStencilViewDesc.Format = depthTexDesc.Format;
		//�Z2D�e�N�X�`�����������Ƃ��w�肷��B
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//�~0�ł����B
		depthStencilViewDesc.Texture2D.MipSlice = 0;
		//�~0�ł����B
		depthStencilViewDesc.Flags = 0;
		//�Z�f�v�X�X�e���V���r���[���쐬�B
		d3dDevice->CreateDepthStencilView(
			m_depthStencilTex,
			&depthStencilViewDesc,
			&m_depthStencilView
		);
	}
	//6.�r���[�|�[�g�̐ݒ�
	{
		m_viewport.Width = w;
		m_viewport.Height = h;
		m_viewport.TopLeftX = 0;
		m_viewport.TopLeftY = 0;
		m_viewport.MinDepth = 0.0f;
		m_viewport.MaxDepth = 1.0f;
		d3dDeviceContext->RSSetViewports(1, &m_viewport);

	}

	//���X�^���C�U�̐ݒ�
	//{
	//	D3D11_RASTERIZER_DESC desc = {};
	//	desc.CullMode = D3D11_CULL_NONE;
	//	desc.FillMode = D3D11_FILL_SOLID;
	//	desc.DepthClipEnable = true;
	//	desc.MultisampleEnable = true;
	//	//���X�^���C�U�ƃr���[�|�[�g���������B
	//	d3dDevice->CreateRasterizerState(&desc, &m_rasterizerState);
	//	d3dDeviceContext->RSSetState(m_rasterizerState);
	//}
}


void RenderTarget::ClearRenderTarget(float* clearColor)
{
	//�����_�����O�^�[�Q�b�g���N���A�B
	//�@�o�@�`�����G���N���A����I�@�p
	auto d3dDeviceContext = g_graphicsEngine->GetD3DDeviceContext();

	d3dDeviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
	d3dDeviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}