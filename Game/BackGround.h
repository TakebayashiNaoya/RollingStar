///
/// �n�ʂƂȂ�N���X
///
#pragma once

class Game;
class Transform;

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	void Rotation();

public:
	Transform* GetTransform()
	{
		return m_transform;
	}

private:
	Game* m_game = nullptr;
	Transform* m_transform = nullptr;

private:
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
	Quaternion m_rotationQuat = Quaternion::Identity;	//������]��P��Quaternion�i����]�j�ŏ�����
	Vector3 m_moveSpeed = Vector3::Zero;
};