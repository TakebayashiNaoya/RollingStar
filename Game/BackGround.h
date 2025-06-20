#pragma once

class Transform;
class Game;

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Rotation();

	void Render(RenderContext& rc);

	Transform* GetTransform()
	{
		return m_transform;
	}

private:
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Quaternion m_rotation;
	Quaternion m_rotationQuat = Quaternion::Identity;	//初期回転を単位Quaternion（無回転）で初期化
	Vector3 m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
	// ↑と同じ意味
	//const Vector3 moveSpeedReset = Vector3::Zero;

	Vector3 m_rotationVelocity = Vector3::Zero;
	Vector3 m_position = Vector3::Zero;
	Transform* m_transform = nullptr;
	Game* m_game;
};