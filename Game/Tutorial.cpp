#include "stdafx.h"
#include "Tutorial.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "CountDown.h"
#include "Game.h"
#include "GameTimer.h"

Tutorial::~Tutorial()
{
	m_countDown = NewGO<CountDown>(0, "countdown");
}

bool Tutorial::Start()
{
	m_spriteRender.Init("Assets/sprite/tutorial.dds", 1280.0f, 900.0f);//•”wŒi
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ƒ{ƒ^ƒ“SE

	return true;
}

void Tutorial::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//ƒ{ƒ^ƒ“SE
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