#pragma once
class Game;
class GameTimer;
class CountDown;

class Tutorial :public IGameObject
{
public:
	Tutorial();
	~Tutorial();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”
	Game* m_game;
	GameTimer* m_gameTimer;
	CountDown* m_countDown;
	SpriteRender m_spriteRender;
	FontRender m_fontRender;
	bool m_startFlag = false;
	bool m_countDownFlag = false;
};

