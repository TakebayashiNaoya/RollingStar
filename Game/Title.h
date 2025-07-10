///
/// タイトルを管理するクラス
///
#pragma once

class Game;

class Title :public IGameObject
{
private:
	enum EnTitleStep {
		enTitleStep_1,
		enTitleStep_2,
		enTitleStep_3,
	};

public:
	~Title();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	Game* m_game = nullptr;
	SoundSource* m_titleBgm = nullptr;

private:
	EnTitleStep m_titleStep;
	SpriteRender m_titleViewSpriteRender;
	FontRender m_fontRender;
};

