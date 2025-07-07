#pragma once
class Game;
class GameTimer :public IGameObject
{
public:
	GameTimer();
	~GameTimer();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//メンバ変数
	Game* m_game;
	FontRender m_fontRender;
	float m_maxTimer = 5.0f;	//制限時間
	float m_timer = 0.0f;		//タイマー
	float m_timeLimit = 0.0f;	//タイムリミット
};