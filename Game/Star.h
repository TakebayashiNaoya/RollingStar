#pragma once

class BackGround;
class Transform;
class Player;
class Score;
class Game;
class StarSpawner;

class Star :public IGameObject
{
public:
	Star();
	~Star();
	bool Start() override;
	void Update();
	void Render(RenderContext& rc);
	void SetTransform(Transform* p)
	{
		m_transform = p;
	};

private:
	void GetStar();

private:
	Game* m_game = nullptr;
	ModelRender				m_modelRender;
	PhysicsStaticObject		m_physicsStaticObject;
	Vector3					m_position;
	//Quaternion				m_rotation;
	//Vector3					m_scale;
	Vector3					m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
	Transform* m_transform = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	StarSpawner* m_starSpawner = nullptr;
};