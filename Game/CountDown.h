#pragma once
class Game;
class CountDown :public IGameObject
{
public:
	CountDown();
	~CountDown();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	//ƒƒ“ƒo•Ï”
	Game* m_game;
	SpriteRender* m_spriteRender;
	SpriteRender m_count3SpriteRender;
	SpriteRender m_count2SpriteRender;
	SpriteRender m_count1SpriteRender;
	SpriteRender m_countStartSpriteRender;

	float countDown = 0;
	int spriteState = 0;
};

