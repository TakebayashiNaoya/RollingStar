#include "stdafx.h"
#include "Tutorial.h"
#include "SoundManager.h"
#include "CountDown.h"
#include "SpriteManager.h"

Tutorial::~Tutorial()
{
	NewGO<CountDown>(0, "countdown");
}

bool Tutorial::Start()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");
	spriteManager->SpriteInit(m_tutorialSpriteRender, enSpriteKinds_Tutorial);

	return true;
}

void Tutorial::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
		soundManager->SoundNewGO(enSoundList_SelectSE);

		DeleteGO(this);
	}
}

void Tutorial::Render(RenderContext& rc)
{
	m_tutorialSpriteRender.Draw(rc);
}