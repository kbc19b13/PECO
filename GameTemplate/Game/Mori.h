#pragma once
class Mori : public IGameObject
{
public:
	Mori()
	{}
	virtual ~Mori()
	{}

	virtual bool Start()
	{
		return true;
	}

	virtual void Update()
	{}

public:
	void SetPosition(const CVector3& pos)
	{
		m_pos = pos;
	}

	const CVector3& GetPositon() const 
	{
		return m_pos;
	}
	void SetMoveSpeed(const CVector3& movespeed)
	{
		m_speed = movespeed;
	}
	const CVector3& GetMoveSpeed() const
	{
		return m_speed;
	}
	void SetRotation(const CQuaternion& rot)
	{
		m_rot = rot;
	}
	const CQuaternion& GetRotation() const
	{
		return m_rot;
	}
	bool IsLive() const
	{
		return m_isLive;
	}
	bool IsDying() const
	{
		m_isCotton;
	}

protected:

	enum State {
		State_Normal,
		State_Dying,
		State_Death
	};
	State m_state = State_Normal;  //ステート

	SkinModel m_moidel;

	CVector3 m_pos = { 0.0f, 0.0f, 0.0f };
	CVector3 m_speed = { 0.0f, 0.0f, 0.0f };
	
	CQuaternion m_rot = { 0.0f, 0.0f, 0.0f , 0.0f };

	bool m_isLive; //生きてる？
	bool m_isCotton;  //綿入ってる？
};

