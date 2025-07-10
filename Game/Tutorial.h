///
/// チュートリアルを管理するクラス
///
#pragma once

class CountDown;
class Game;
class GameTimer;

class Tutorial :public IGameObject
{
public:
	~Tutorial();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	Game* m_game = nullptr;
	GameTimer* m_gameTimer = nullptr;
	CountDown* m_countDown = nullptr;

private:
	SpriteRender m_spriteRender;
	FontRender m_fontRender;
	bool m_startFlag = false;
	bool m_countDownFlag = false;
};

