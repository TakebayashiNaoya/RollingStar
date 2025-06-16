#pragma once

class BackGround;
class Transform;
class Player;
class Score;
class Game;

class Star :public IGameObject
{
public:
	Star();
	~Star();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Vector3 GetPosition()
	{
		return m_position;
	}

	Transform* GetTransform()
	{
		return m_transform;
	}

	Game* m_game;

private:
	ModelRender				m_modelRender;
	PhysicsStaticObject		m_physicsStaticObject;
	Quaternion				m_rotation;
	Vector3					m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
	Vector3					m_position;
	Transform* m_transform = nullptr;
	BackGround* m_backGround = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
};