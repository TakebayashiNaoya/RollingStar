///
/// インゲームの時間を管理するクラス
///
#pragma once

class Game;

class GameTimer :public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

public:
	float GetTimeLimit()
	{
		return m_timeLimit;
	}

private:
	Game* m_game = nullptr;

private:
	FontRender m_timeLimitfontRender;
	float m_timer = 0.0f;
	float m_timeLimit = 0.0f;
};