/// <summary>
/// スタースポナーを管理するクラス
/// </summary>
#pragma once

class BackGround;
class Star;
class Transform;

class StarSpawner :public IGameObject
{
public:
	StarSpawner();
	~StarSpawner();

	/// <summary>
	/// m_transform メンバーへのポインタを取得します。
	/// </summary>
	/// <returns>Transform 型のポインタ。m_transform メンバーへのポインタを返します。</returns>
	Transform* GetTransform()
	{
		return m_transform;
	}

private:
	bool Start()override final;
	void Update()override final;

	BackGround* m_backGround = nullptr;
	Star* m_star = nullptr;
	Transform* m_transform = nullptr;

	float m_respawnTimer = 0.0f;	// スターのリスポーン時間を格納する。
};
