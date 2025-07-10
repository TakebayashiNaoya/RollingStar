///
/// ゲームスタート時のカウントダウンクラス
///
#pragma once

class Game;

class CountDown :public IGameObject
{
public:
	CountDown();
	~CountDown();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	SpriteRender* ComputeSpriteRender();

private:
	Game* m_game = nullptr;

private:
	SpriteRender m_count3SpriteRender;
	SpriteRender m_count2SpriteRender;
	SpriteRender m_count1SpriteRender;
	SpriteRender m_countStartSpriteRender;
	SpriteRender* m_spriteRender = nullptr;

	float countDown = 0.0f;
	int spriteState = 0;
};

