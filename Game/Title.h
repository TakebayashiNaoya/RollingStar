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

	//ƒƒ“ƒo•Ï”
	SpriteRender m_spriteRender;
	Tutorial* m_tutorial;
	FontRender m_fontRender;
	SoundSource* m_titleBgm;
};

