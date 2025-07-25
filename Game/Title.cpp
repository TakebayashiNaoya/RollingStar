#include "stdafx.h"
#include "Title.h"
#include "SoundManager.h"
#include "Game.h"
#include "LoadingView.h"

Title::~Title()
{
	NewGO<Game>(0, "game");

	SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
	soundManager->SoundDeleteGO(enSoundList_TitleBGM);
}

bool Title::Start()
{
	m_titleViewSpriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);

	SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
	soundManager->SoundNewGO(enSoundList_TitleBGM);

	return true;
}

void Title::Update()
{
	switch (m_titleStep)
	{
	case enTitleStep_1:

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_SelectSE);

			NewGO<LoadingView>(0, "loadingview");

			m_titleStep = enTitleStep_2;
		}
		break;

	case enTitleStep_2:
		//1ƒtƒŒ[ƒ€‘Ò‚Â‚½‚ß
		m_titleStep = enTitleStep_3;
		break;

	case enTitleStep_3:
		DeleteGO(this);
		break;

	default:
		break;
	}
}

void Title::Render(RenderContext& rc)
{
	m_titleViewSpriteRender.Draw(rc);
}