#pragma once

class Star;
class Transform;
class BackGround;

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
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;
	ModelRender m_modelRender;
	Transform* m_transform = nullptr;
	BackGround* m_backGround = nullptr;
	Star* m_star = nullptr;
	float m_respawnTimer = 0.0f;
};
