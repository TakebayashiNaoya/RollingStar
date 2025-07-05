#pragma once

class BackGround;
class Transform;
class Player;
class Score;
class Game;
class StarSpawner;
class PopScoreManager;

class Star :public IGameObject
{
public:
	~Star();
	bool Start() override;
	void Update()override;
	void Render(RenderContext& rc);
	void SetTransform(Transform* p)
	{
		m_transform = p;
	};

	bool isDead = false;
	int starColor;

private:
	void SetStarColor();
	void SetInit();
	void GetStar();
	void GetStarSE();
	void GetStarCounter();
	void Rotation();

private:
	Game* m_game = nullptr;
	ModelRender				m_modelRender;
	Vector3					m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
	Transform* m_transform = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	PopScoreManager* m_popScoreManager = nullptr;
	Vector3 m_position;
	Quaternion m_rotation;
};