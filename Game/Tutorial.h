/// <summary>
/// チュートリアルを管理するクラス
/// </summary>
#pragma once

class CountDown;
class Game;
class GameTimer;

class Tutorial :public IGameObject
{
public:
	~Tutorial();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	SpriteRender m_spriteRender;	// チュートリアル画面を表示する。
	bool m_countDownFlag = false;	// カウントダウンを開始するフラグ。
};

