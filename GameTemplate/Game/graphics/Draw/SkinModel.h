#pragma once

#include "..//Skeleton.h"

const int Number_Direcyion_Light = 4;

/*!
*@brief	FBXの上方向。
*/
enum EnFbxUpAxis {
	enFbxUpAxisY,		//Y-up
	enFbxUpAxisZ,		//Z-up
};
/*!
*@brief	スキンモデルクラス。
*/
class SkinModel
{
public:
	//メッシュが見つかったときのコールバック関数。
	using OnFindMesh = std::function<void(const std::unique_ptr<DirectX::ModelMeshPart>&)>;
	/*!
	*@brief	デストラクタ。
	*/
	~SkinModel();
	
	/*!
	*@brief	初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*@param[in] enFbxUpAxis		fbxの上軸。デフォルトはenFbxUpAxisZ。
	*/
	void Init(const wchar_t* filePath, EnFbxUpAxis enFbxUpAxis = enFbxUpAxisZ);
	/*!
	*@brief	モデルをワールド座標系に変換するためのワールド行列を更新する。
	*@param[in]	position	モデルの座標。
	*@param[in]	rotation	モデルの回転。
	*@param[in]	scale		モデルの拡大率。
	*/
	void UpdateWorldMatrix(CVector3 position, CQuaternion rotation, CVector3 scale);
	/*!
	*@brief	ボーンを検索。
	*@param[in]		boneName	ボーンの名前。
	*@return	見つかったボーン。見つからなかった場合はnullptrを返します。
	*/
	Bone* FindBone(const wchar_t* boneName)
	{
		int boneId = m_skeleton.FindBoneID(boneName);
		return m_skeleton.GetBone(boneId);
	}
	/*!
	*@brief	モデルを描画。
	*@param[in]	viewMatrix		カメラ行列。
	*  ワールド座標系の3Dモデルをカメラ座標系に変換する行列です。
	*@param[in]	projMatrix		プロジェクション行列。
	*  カメラ座標系の3Dモデルをスクリーン座標系に変換する行列です。
	*@param[in] renderMode		描画モード
	*	GraphicsEngine.h の EnRenderMode を参照。
	*/
	void Draw( CMatrix viewMatrix, CMatrix projMatrix , EnRenderMode rendermode);
	/*!
	*@brief	スケルトンの取得。
	*/
	Skeleton& GetSkeleton()
	{
		return m_skeleton;
	}
	/*!
	*@brief	メッシュを検索する。
	*@param[in] onFindMesh		メッシュが見つかったときのコールバック関数
	*/
	void FindMesh(OnFindMesh onFindMesh) const
	{
		for (auto& modelMeshs : m_modelDx->meshes) {
			for (std::unique_ptr<DirectX::ModelMeshPart>& mesh : modelMeshs->meshParts) {
				onFindMesh(mesh);
			}
		}
	}

	/// <summary>
	/// シャドウレシーバーのフラグを設定する。
	/// </summary>
	/// <param name="flag">trueを渡すとシャドウレシーバーになる</param>
	/// <remarks>
	/// シャドウレシーバーとは影を落とされるオブジェクトのことです。
	/// シャドウキャスターによって生成された、シャドウマップを利用して
	/// 自身に影を落とします。
	/// オブジェクトがシャドウレシーバーかつシャドウキャスターになっている場合は
	/// セルフシャドウ(自分の影が自分に落ちる)を行うことができます。
	/// </remarks>
	void SetShadowReciever(bool flag)
	{
		m_isShadowReciever = flag;
	}


	/*!
	*@brief	SRVのレジスタ番号。
	*/
	enum EnSkinModelSRVReg {
		enSkinModelSRVReg_DiffuseTexture = 0,		//!<ディフューズテクスチャ。
		enSkinModelSRVReg_BoneMatrix,				//!<ボーン行列。
	};
private:
	/*!
	*@brief	サンプラステートの初期化。
	*/
	void InitSamplerState();
	/*!
	*@brief	定数バッファの作成。
	*/
	void InitConstantBuffer();
	/*!
	*@brief	スケルトンの初期化。
	*@param[in]	filePath		ロードするcmoファイルのファイルパス。
	*/
	void InitSkeleton(const wchar_t* filePath);

	/// <summary>
	/// ディレクションライトの初期化。
	/// </summary>
	void InitDirectionLight();
	
	
private:


	/// <summary>
	/// ディレクションライト
	/// </summary>
	/// 要素数の指定_const変数
	/// Number_Direcyion_Light == 4
	struct SDirectionLight {
		CVector4 direction[Number_Direcyion_Light];		//ライトの方向。
		CVector4 color[Number_Direcyion_Light];			//ライトのカラー。
	};

	/// <summary>
	/// ライトの構造体
	/// </summary>
	struct SLight {
		SDirectionLight		directionLight;		//ディレクションライト
		CVector3			eyePos;				//視点の座標。
		float				specPow;			//鏡面反射の絞り。
	};

	int Raundup16(int n)
	{
		return (((n - 1) / 16) + 1) * 16;
	}

	//定数バッファ。
	struct SVSConstantBuffer {
		CMatrix mWorld;
		CMatrix mView;
		CMatrix mProj;
		//シャドウマップ用ライトビュー行列を追加。
		CMatrix mLightView;	//ライトビュー行列。
		CMatrix mLightProj;	//ライトプロジェクション行列。
		int isShadowReciever;	//シャドウレシーバーフラグ。
	};
	EnFbxUpAxis			m_enFbxUpAxis = enFbxUpAxisZ;	//!<FBXの上方向。
	ID3D11Buffer*		m_cb = nullptr;					//!<定数バッファ。
	Skeleton			m_skeleton;						//!<スケルトン。
	CMatrix				m_worldMatrix;					//!<ワールド行列。
	DirectX::Model*		m_modelDx;						//!<DirectXTKが提供するモデルクラス。
	ID3D11SamplerState* m_samplerState = nullptr;		//!<サンプラステート。
	ID3D11ShaderResourceView* m_albedoTextureSRV = nullptr;	//!<アルベドテクスチャのSRV
	
	ID3D11Buffer*		m_lightCb = nullptr;			//!<ライト用の定数バッファ。
	SDirectionLight		m_dirLight;						//!<ディレクションライト。

	SLight				m_light;						//!<ライト構造体。ライト用の構造体を使うように変更。
	
	bool m_isShadowReciever = true;						//シャドウレシーバーフラグ。

	
};

