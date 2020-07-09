//ゲームオブジェクトの基底クラス

#pragma once

namespace mtEngine {
	//?
	class mtGameObjectManager;
	typedef unsigned char	GameObjectPrio;//優先度
	//typedef別名定義

	class IGameObject
	{
	public:
		/*
		コンストラクタ初期化

		優先度
		スタートしているか
		死んでいないか
		NewGOで作られたか
		*/
		IGameObject() :
			m_priority(0),
			m_isStart(false),
			m_isDead(false),
			m_isNewFromGameObjectManager(false)
		{
		}
		/*!
		 *@brief	デストラクタ
		 */
		virtual ~IGameObject()
		{
		}

		/*!
	*@brief	Updateの直前で呼ばれる開始処理。
	*@details
	* 本関数がtrueを返すとゲームオブジェクトの準備が完了したと判断されて</br>
	* Update関数が呼ばれ出します。trueを返して以降はStart関数は呼ばれなくなります。</br>
	* ゲームオブジェクトの初期化に複数フレームかかる場合などはfalseを返して、初期化ステップなどを使って</br>
	* 適切に初期化を行ってください。
	*/
		virtual bool Start() { return true; }
		/*!
		 *@brief	更新処理
		 */
		virtual void Update() {}

		/*!
	 *@brief	削除されるときに呼ばれる。
	 *@details	CGameManager::DeleteGameObjectを呼んだときに実行されます。
	 * デストラクタより前に実行されます。
	 */
		virtual void OnDestroy() {}
		/*!
		*@brief	実行優先度を取得。
		*/
		GameObjectPrio GetPriority() const
		{
			return m_priority;
		}
		/*!
		*@brief	死亡フラグを立てる。
			* @details
			* この関数はエンジンの外からは実行しないでください。
		*/
			void SetDeadMark()
		{
			m_isDead = true;
		}
		/*!
		*@brief	死亡判定。
		*/
		bool IsDead() const
		{
			return m_isDead;
		}
		/*!
		*@brief Start関数が完了した？
		*/
		virtual bool IsStart() const
		{
			return m_isStart;
		}
		/*!
		*@brief アクティブかどうかを判定。
		*/
		bool IsActive() const
		{
			return m_isActive;
		}
		/*!
		*@brief アクティブフラグを設定。
		*/
		void SetActiveFlag(bool flag)
		{
			m_isActive = flag;
		}
		/*!
		*@brief タグを設定。
		*/
		void SetTags(unsigned int tags)
		{
			m_tags = tags;
		}
		/*!
		*@brief タグを取得。
		*/
		unsigned int GetTags() const
		{
			return m_tags;
		}
		/*
		*@brief Updateを呼んでもいい状況か判定
		*/
		void UpdateWrapper()
		{
			if (m_isActive && m_isStart && !m_isDead && !m_isRegistDeadList) {
				Update();
			}
		}
		/*
		*@brief Startを呼んでもいい状況か判定
		*/
		void StartWrapper()
		{
			if (m_isActive && !m_isStart && !m_isDead && !m_isRegistDeadList) {
				if (Start()) {
					//初期化処理完了。
					m_isStart = true;
				}
			}
		}
		/*
		*@brief OnDestroyを呼んでもいい状況か判定
		*/
		void OnDestroyWrapper()
		{

			OnDestroy();

		}
		/*
		*@brief NewGOで生成されたのでtrueを渡す
		*/
		void SetMarkNewFromGameObjectManager()
		{
			m_isNewFromGameObjectManager = true;
		}
		/*
		*@brief NewGOで生成されているかの判定
		*/
		bool IsNewFromGameObjectManager() const
		{
			return m_isNewFromGameObjectManager;
		}


		friend class mtGameObjectManager;
	protected:
		GameObjectPrio	m_priority;			//!<実行優先度。
		bool m_isStart;						//!<Startの開始フラグ。
		bool m_isDead;						//!<死亡フラグ。
		bool m_isRegistDeadList = false;	//!<死亡リストに登録。
		bool m_isNewFromGameObjectManager;	//!<GameObjectManagerでnewされた。
		bool m_isRegist = false;			//!<GameObjectManagerに登録されている？
		bool m_isActive = true;				//!<Activeフラグ_trueならUpdateが呼ばれる。
		unsigned int m_tags = 0;			//!<タグ。
		unsigned int m_nameKey = 0;			//!<名前キー。

	};

}