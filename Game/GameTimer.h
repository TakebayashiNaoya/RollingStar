/// <summary>
/// インゲームの時間を管理するクラス
/// </summary>
#pragma once

class Game;

class GameTimer :public IGameObject
{
public:
	/// <summary>
	/// 制限時間を取得します。
	/// </summary>
	float GetTimeLimit()const
	{
		return m_timeLimit;
	}

private:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	Game* m_game = nullptr;

	FontRender m_timeLimitfontRender;	// 制限時間のフォントを表示するために使用します。
	float m_timer = 0.0f;				// 経過時間を格納する変数です。
	float m_timeLimit = 0.0f;			// 残り時間を格納する変数です。
};