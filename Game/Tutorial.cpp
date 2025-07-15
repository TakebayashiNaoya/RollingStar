#include "stdafx.h"
#include "Tutorial.h"

#include "SoundManager.h"

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

	return true;
}

void Tutorial::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		SoundNewGO(enSoundList_SelectSE);

		DeleteGO(this);
	}
}

void Tutorial::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}