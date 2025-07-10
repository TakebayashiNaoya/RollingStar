#pragma once

class BackGround;
class Star;
class Transform;

class StarSpawner :public IGameObject
{
public:
	StarSpawner();
	~StarSpawner();
	bool Start();
	void Update();

	Transform* GetTransform()
	{
		return m_transform;
	}

private:
	BackGround* m_backGround = nullptr;
	Star* m_star = nullptr;
	Transform* m_transform = nullptr;

private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::Zero;
	Quaternion m_rotation;
	ModelRender m_modelRender;
	float m_respawnTimer = 0.0f;
};
