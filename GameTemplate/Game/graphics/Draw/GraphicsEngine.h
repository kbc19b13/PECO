#pragma once
#include "RenderTarget.h"
#include "graphics/Draw/ShadowMap.h"
#include "Sprite.h"

/// <summary>
/// �����_�����O���[�h
/// </summary>
enum EnRenderMode
{
	enRenderMode_Normal,		//�ʏ�`��
	enRenderMode_Silhouette,	//�V���G�b�g�`��
	enRenderMode_ShadowMap,		//�V���h�E�}�b�v�`��
};
/*!
 *@brief	�O���t�B�b�N�X�G���W���B
 */
class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
	/*!
	 *@brief	�������B
	 *@param[in]	hWnd		�E�B���h�E�n���h���B
	 */
	void Init(HWND hWnd);
	/// <summary>
	/// �G�t�F�N�T�[�̏�����
	/// </summary>
	void InitEffekseer();
	/*!
	 *@brief	����B
	 */
	void Release();
	/*!
	 *@brief	D3D11�f�o�C�X���擾�B
	 */
	ID3D11Device* GetD3DDevice()
	{
		return m_pd3dDevice;
	}
	/*!
	 *@brief	D3D11�f�o�C�X�R���e�L�X�g���擾�B
	 */
	ID3D11DeviceContext* GetD3DDeviceContext()
	{
		return m_pd3dDeviceContext;
	}
	/*!
	 *@brief	�`��J�n�B
	 */
	void BegineRender();

	/// <summary>
	/// ���O�����_�����O
	/// </summary>
	void PreRender();
	/// <summary>
	/// ���C�������_�����O
	/// </summary>
	void ForwordRender();
	/// <summary>
	/// �|�X�g�G�t�F�N�g�����_�����O
	/// </summary>
	void PostRender();

	/*!
	 *@brief	�`��I���B
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
		//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
		m_pd3dDeviceContext->OMSetRenderTargets(1, rtTbl, depthStensil);
		if (viewport != nullptr) {
			//�r���[�|�[�g���w�肳��Ă�����A�r���[�|�[�g���ύX����B
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
	//�r���[�|�[�g��ݒ�B
	m_pd3dDeviceContext->RSSetViewports(1, m_3dObjectRenderTarget.GetViewport());
		*/
	}
	/// <summary>
	/// �V���h�E�}�b�v���擾�B
	/// </summary>
	/// <returns></returns>
	ShadowMap* GetShadowMap()
	{
		return &m_shadowMap;
	}

	/// <summary>
	/// �����_�[�^�[�Q�b�g�r���[�̎擾
	/// </summary>
	/// <returns></returns>
	ID3D11RenderTargetView* GetBackBuffer()
	{
		return m_backBuffer;
	}

	/// <summary>
	/// 3D�I�u�W�F�N�g�̃����_�[�^�[�Q�b�g���擾
	/// </summary>
	/// <returns></returns>
	RenderTarget& Get3DObjectRenderTarget()
	{
		return m_3dObjectRenderTarget;
	}

	/// <summary>
	/// �����o�����_�[�^�[�Q�b�g���擾
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
	D3D_FEATURE_LEVEL		m_featureLevel;					//Direct3D �f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g�B
	ID3D11Device*			m_pd3dDevice = NULL;			//D3D11�f�o�C�X�B
	IDXGISwapChain*			m_pSwapChain = NULL;			//�X���b�v�`�F�C���B
	ID3D11DeviceContext*	m_pd3dDeviceContext = NULL;		//D3D11�f�o�C�X�R���e�L�X�g�B
	ID3D11RenderTargetView* m_backBuffer = NULL;			//�o�b�N�o�b�t�@�B
	ID3D11RasterizerState*	m_rasterizerState = NULL;		//���X�^���C�U�X�e�[�g�B
	ID3D11Texture2D*		m_depthStencil = nullptr;		//�f�v�X�X�e���V���ƂȂ�e�N�X�`���B
	ID3D11DepthStencilView* m_depthStencilView = nullptr;	//!<�f�v�X�X�e���V���r���[�B

	ShadowMap m_shadowMap;									//�V���h�E�}�b�v�B

															//�����_�����O�^�[�Q�b�g�֌W�̃����o�ϐ��ł��B
	//�����_�����O�^�[�Q�b�g�̉������y�ɂ��邽�߂ɍ쐬
	RenderTarget m_renderTarget;							//todo �����_�����O�^�[�Q�b�g

	RenderTarget m_3dObjectRenderTarget;					//todo 3D�I�u�W�F�N�g�������_�����O���邽�߂̃����_�����O�^�[�Q�b�g�B
	Sprite m_copy3dObjectRtToFrameBufferSprite;				//todo 3D�I�u�W�F�N�g���`���ꂽ�e�N�X�`�����t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g�B

	//Effekseer�}�l�[�W���Ǘ��B
	Effekseer::Manager* m_effekseerManager = nullptr;
	EffekseerRenderer::Renderer* m_effekseerRenderer = nullptr;
	
	D3D11_VIEWPORT m_frameBufferViewports;					//�t���[���o�b�t�@�̃r���[�|�[�g�B

	ID3D11RenderTargetView* oldRenderTargetView = nullptr;	//�t���[���o�b�t�@�̃����_�����O�^�[�Q�b�g�r���[�B
	ID3D11DepthStencilView* oldDepthStencilView = nullptr;	//�t���[���o�b�t�@�̃f�v�X�X�e���V���r���[�B

};

extern GraphicsEngine* g_graphicsEngine;				//�O���t�B�b�N�X�G���W��