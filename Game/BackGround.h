/// <summary>
/// 地面となるクラス
/// </summary>
#pragma once

class Game;
class Transform;

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

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
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// 回転操作を実行します。
	/// </summary>
	void Rotation();

	Game* m_game = nullptr;
	Transform* m_transform = nullptr;

	ModelRender	m_modelRender;							// モデルの描画を管理する ModelRender 型のオブジェクト。
	PhysicsStaticObject m_physicsStaticObject;			// 当たり判定の実装。
	Quaternion m_rotationQuat = Quaternion::Identity;	// 初期回転を単位Quaternion（無回転）で初期化。
	Vector3	m_rotationVector = Vector3::Zero;			// 回転ベクトルを初期化。
};