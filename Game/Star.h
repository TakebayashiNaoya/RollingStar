///
/// スターを管理するクラス
///
#pragma once

class Game;
class Player;
class PopScoreManager;
class Score;
class Transform;

class Star :public IGameObject
{
public:
	~Star();
	bool Start() override;
	void Update()override;
	void Render(RenderContext& rc)override;


	bool isDead = false;
	int starColor;

public:
	void SetTransform(Transform* p)
	{
		m_transform = p;
	}

private:
	void SetStarColor();
	void SetInit();
	void GetStar();
	void Rotation();

private:
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	PopScoreManager* m_popScoreManager = nullptr;
	Score* m_score = nullptr;
	Transform* m_transform = nullptr;

private:
	ModelRender	m_modelRender;
	Vector3		m_moveSpeed = Vector3::Zero;
	Vector3		m_position = Vector3::Zero;
	Quaternion	m_rotation;
};