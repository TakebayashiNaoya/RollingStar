#pragma once
#include "sound/SoundSource.h"

class Tutorial;
class Game;

class Title :public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	enum EnTitleStep {
		enTitleStep_1,
		enTitleStep_2,
		enTitleStep_3,
	};

	//ƒƒ“ƒo•Ï”
	EnTitleStep m_titleStep;
	SpriteRender m_spriteRender;
	Game* m_game = nullptr;
	FontRender m_fontRender;
	SoundSource* m_titleBgm;
};

