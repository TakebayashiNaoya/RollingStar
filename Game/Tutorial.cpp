#include "stdafx.h"
#include "Tutorial.h"
#include "GameTimer.h"
#include "Game.h"
#include "CountDown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{
	m_countDown = NewGO<CountDown>(0, "countdown");
}

bool Tutorial::Start()
{
	m_spriteRender.Init("Assets/sprite/tutorial.dds", 1280.0f, 900.0f);//黒背景
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE

	//m_game = NewGO<Game>(0, "game");
	//m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	return true;
}

void Tutorial::Update()
{
	//Aを押してスタート
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//ボタンSE
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(6);
		se->Play(false);
		se->SetVolume(3.5f);

		DeleteGO(this);
	}
}

void Tutorial::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}