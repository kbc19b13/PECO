#pragma once


#ifndef _CGAMEOBJECTMANAGER_H_
#define _CGAMEOBJECTMANAGER_H_

#include "../GameObject/mtGameObject.h"
#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include "../util/mtUtil.h"
#include "../graphics/Draw/Sprite.h"

/*!
	*@brief	CGameObjectのマネージャ
	*/
class mtGameObjectManager
{
private:
	mtGameObjectManager();
	~mtGameObjectManager()
	{
	}
	/*!
*@brief	ゲームオブジェクトの名前キーを作成。
	静的関数　namespaceで呼び出せる
*/
	static unsigned int MakeGameObjectNameKey(const char* objectName)
	{
		//デフォルトの名前　＝　未定義
		static const unsigned int defaultNameKey = CUtil::MakeHash("Undefined");	//名前キー。
		unsigned int hash;
		//名前を未定義にする
		if (objectName == nullptr) {
			hash = defaultNameKey;
		}
		//自分の名前を返す
		else {
			hash = CUtil::MakeHash(objectName);
		}
		return hash;
	}
public:
	/*!
	*@brief	インスタンスの取得。
	*///静的メンバ関数(どこからでも呼び出せる)
	static mtGameObjectManager& Instance()
	{
		//限定したグローバル変数
		static mtGameObjectManager instance;
		return instance;
	}
	/// メインスレッドから呼ばれる実行処理。
		/// </summary//概要>
	void ExecuteFromMainThread();//Start
	/*!
	*@brief	ゲームスレッドから呼ばれる実行処理。
	*/
	void ExecuteFromGameThread();//Updeta
	/// <summary>
	/// todo 描画スレッドから呼ばれる実行処理
	/// </summary>
	//void ExecuteFromDrawThread();//Draw
	/*!
	*@brief	初期化。
	*@param[in]	gameObjectPrioMax	ゲームオブジェクトの優先度の最大値。(255まで)
	*/
	void Init(int gameObjectPrioMax);
	/*!
		*@brief	ゲームオブジェクトの追加。
		*@param[in]	prio			実行優先順位。
		*@param[in] go				ゲームオブジェクト
		*@param[in] objectName		オブジェクト名
		*/
	void AddGameObject(GameObjectPrio prio, IGameObject* go, const char* objectName = nullptr)
	{
		//引数3のオブジェクト名
		//引数のない戻り値(void) = オブジェクト名は返さない
		(void)objectName;
		//GameObjectManagerに登録されているか
		if (!go->m_isRegist) {
			//go->Awake();//　またね(@^^)/~~~
			//ハッシュ値　＝　メモリ小、文字より数字のほうが早い
			//名前を数値として保管
			unsigned int hash = MakeGameObjectNameKey(objectName);
			//at　＝ <vector>要素アクセス.<list>末尾に要素を追加する
			m_gameObjectListArray.at(prio).push_back(go);
			//GameObjectManagerに登録されている
			go->m_isRegist = true;
			//引数1の実行優先度を設定
			go->m_priority = prio;
			//Startはまだされていない
			go->m_isStart = false;
			//MakeGameObjectNameKey()の戻り値を記録
			go->m_nameKey = hash;

			if (go->m_isDead) {
				//死亡フラグが立っている。
				//削除リストに入っていたらそこから除去する。
				go->m_isDead = false;
			}

		}
	}
	/*!
			*@brief	ゲームオブジェクトのnew
			*@details
			* この関数を使用してnewしたオブジェクトは必ずDeleteGameObjectを実行することでdeleteされます。
			*@param[in]	prio		実行優先順位。
			*@param[in]	objectName	オブジェクト名。
			*/
	template<class T, class... TArgs>	//テンプレ
	T* NewGameObject(GameObjectPrio prigo, const char* objectName)
	{
		/*
		テンプレートがわからなくなったら
		https://qiita.com/hal1437/items/b6deb22a88c76eeaf90c
		*/
		(void*)objectName;
		//TK_ASSERT(prigo <= m_gameObjectPriorityMax, "ゲームオブジェクトの優先度の最大数が大きすぎます。");
		T* newObject = new T();

		//newObject->Awake();
			
		newObject->SetMarkNewFromGameObjectManager();
		//at　＝ <vector>要素アクセス.<list>末尾に要素を追加する
		m_gameObjectListArray.at(prigo).push_back(newObject);
		//ハッシュ値　＝　メモリ小、文字より数字のほうが早い
		//名前を数値として保管
		unsigned int hash = MakeGameObjectNameKey(objectName);
		//GameObjectManagerに登録されている
		newObject->m_isRegist = true;
		//引数1の実行優先度を設定
		newObject->m_priority = prigo;
		//MakeGameObjectNameKey()の戻り値を記録
		newObject->m_nameKey = hash;

		//設定した値を返す
		return newObject;
	}
	/*!
		*@brief	ゲームオブジェクトの削除。
		*/
	void DeleteGameObject(IGameObject* gameObject)
	{
		if (gameObject != nullptr
			&& gameObject->m_isRegist
			) {
			gameObject->SetDeadMark();
			gameObject->OnDestroyWrapper();
			gameObject->m_isRegist = false;
			gameObject->m_isRegistDeadList = true;

			m_deleteObjectArray[m_currentDeleteObjectBufferNo].at(gameObject->GetPriority()).push_back(gameObject);
			gameObject = nullptr;
		}
	}
	/*!
	*@brief	ゲームオブジェクトの検索。
	*@details
	* 重いよ！
	*@param[in]	objectName		オブジェクト名。
	*/
	template<class T>
	T* FindGameObject(const char* objectName, bool enableErrorMessage)
	{
		unsigned int nameKey = CUtil::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//見つけた。
					T* p = dynamic_cast<T*>(go);
					if (p == nullptr && enableErrorMessage == true) {
						//型変換に失敗。

						//TK_WARNING_MESSAGE_BOX(
						//	"FingGameObject ： 型変換に失敗しました。テンプレート引数を確認してください。typeName = %s, objectName = %s",
						//	typeid(T).name(),
						//	objectName
						//);
					}
					return p;
				}
			}
		}
		if (enableErrorMessage == true) {
			/*TK_WARNING_MESSAGE_BOX("FindGO関数に指定された名前のインスタンスを見つけることができませんでした。\n"
				"名前が間違っていないか確認をして下さい。\n"
				"\n\n検索された名前 【%s】\n", objectName);*/
		}
		//見つからなかった。
		return nullptr;
	}
	template<class T>
	void FindGameObjects(const char* objectName, std::function<bool(T* go)> func)
	{
		unsigned int nameKey = CUtil::MakeHash(objectName);
		for (auto goList : m_gameObjectListArray) {
			for (auto go : goList) {
				if (go->m_nameKey == nameKey) {
					//見つけた。
					T* p = dynamic_cast<T*>(go);
					if (func(p) == false) {
						//クエリ中断。
						return;
					}
				}
			}
		}
	}
private:
	/*!
	*@brief	ゲームオブジェクトの削除を実行。
	*/
	void ExecuteDeleteGameObjects();
	/*!
	*@brief	シーングラフの更新。
	*/
	void UpdateSceneGraph();

	void Start();
	void Update();
	void Draw();
		
private:
	typedef std::list<IGameObject*>	mtGameObjectList;
	std::vector<mtGameObjectList>	m_gameObjectListArray;					//!<ゲームオブジェクトの優先度付きリスト。
	std::vector<mtGameObjectList>	m_deleteObjectArray[2];					//!<削除するオブジェクトのリスト。削除処理を行っている最中にDeleteGameObjectが呼ばれる可能性が高いので、ダブルバッファ化。
	GameObjectPrio					m_gameObjectPriorityMax;				//!<ゲームオブジェクトの優先度の最大数。
	int								m_currentDeleteObjectBufferNo = 0;		//!<現在の削除オブジェクトのバッファ番号。
	static const unsigned char 		GAME_OBJECT_PRIO_MAX = 255;				//!<ゲームオブジェクトの優先度の最大値。
	
	unsigned int					gameObjectPrioMax = 32;					//優先度の最大数

	Sprite m_copyMainRtToFrameBufferSprite;
};

//シングルトン（インスタンス取得）
static inline mtGameObjectManager& GameObjectManager()
{
	return mtGameObjectManager::Instance();
}
/*!
*@brief	ゲームオブジェクトの検索のヘルパー関数。
*@details
* 名前の検索が入るため遅いです。
*@param[in]	objectName	ゲームオブジェクトの名前。
*@param[in] enableErrorMessage	エラーメッセージが有効？
*　呼び出し側でnullptrの判定を行いたい場合は、第二引数にfalseを指定して、エラーメッセージの処理を無効にしてください。
*
*@return 見つかったインスタンスのアドレス。見つからなかった場合はnullptrを返す。
*/
template<class T>
static inline T* FindGO(const char* objectName, bool enableErrorMessage = true)
{
	return GameObjectManager().FindGameObject<T>(objectName, enableErrorMessage);
}
/*!
*@brief	ゲームオブジェクトの検索のヘルパー関数。
*@details
* 同名のゲームオブジェクトに全てに対して、クエリを行いたい場合に使用してください。
*@param[in]	objectName	ゲームオブジェクトの名前。
*@param[in]	func		ゲームオブジェクトが見つかったときに呼ばれるコールバック関数。
*/
template<class T>
static inline void QueryGOs(const char* objectName, std::function<bool(T* go)> func)
{
	return GameObjectManager().FindGameObjects<T>(objectName, func);
}
/*!
	*@brief	ゲームオブジェクト生成のヘルパー関数。
	*@param[in]	priority	プライオリティ = 実行優先度
	*@param[in]	objectName	オブジェクト名。(NULLの指定可）
	*@details
	よくあるコンパイルエラー　よくあるコンパイルエラー　よくあるコンパイルエラー　よくあるコンパイルエラー
	Ｑ
	Ｑ
	Ｑ　　　  【１】 public IGameObjectを忘れてない？
	Ｑ　　　  【２】 #includeしてる？
	Ｑ
	Ｑ
	よくあるコンパイルエラー　よくあるコンパイルエラー　よくあるコンパイルエラー　よくあるコンパイルエラー
	*/
	template<class T>
	static inline T* NewGO(
	int priority, 
	const char* objectName = nullptr, 
	typename T::IGameObjectIsBase* = nullptr
)
{
	return GameObjectManager().NewGameObject<T>((GameObjectPrio)priority, objectName);
}

/*!
	*@brief	ゲームオブジェクト削除のヘルパー関数。
	* NewGOを使用して作成したオブジェクトは必ずDeleteGOを実行するように。
	*@param[in]	go		削除するゲームオブジェクト。
	*/
static inline void DeleteGO(IGameObject* go)
{
	GameObjectManager().DeleteGameObject(go);
}
/*!
	*@brief	ゲームオブジェクト削除のヘルパー関数。
	* NewGOを使用して作成したオブジェクトは必ずDeleteGOを実行するように。
	*@details
	* 名前の検索が入るため遅いです。
	*@param[in]	objectName		削除するゲームオブジェクトの名前。
	*/
static inline void DeleteGO(const char* objectName)
{
	IGameObject* go = FindGO<IGameObject>(objectName);
	GameObjectManager().DeleteGameObject(go);
}
/*!
*@brief	ゲームオブジェクトを名前指定で削除。
*@details
* 名前検索が行われるため遅いです。
*@param[in]	objectName		削除するゲームオブジェクトの名前。
*/
static inline void DeleteGOs(const char* objectName)
{
	QueryGOs<IGameObject>(objectName, [](auto go) {
		DeleteGO(go);
		return true;
		});
}

#endif // _CGAMEOBJECTMANAGER_H_