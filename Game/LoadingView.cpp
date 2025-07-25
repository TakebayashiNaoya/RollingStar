#include "stdafx.h"
#include "LoadingView.h"
#include "SoundManager.h"
#include "Tutorial.h"
#include "Type.h"

namespace
{
	const Vector4 FONT_COLOR = { 0.9f, 0.9f, 1.0f, 1.0f };	// 青みがかった白。
	const Vector2 FONT_POSITION = { 450.0f, -350.0f };		// PUSH(A)の位置。
	const float FONT_SIZE = 2.0f;							// PUSH(A)のサイズ。
}

LoadingView::~LoadingView()
{
	NewGO<Tutorial>(0, "tutorial");
}

bool LoadingView::Start()
{
	m_LoadingSceneSpriteRender.Init("Assets/sprite/LoadingView.dds", 1920.0f, 1080.0f);

	m_LoadingPhaseSpriteRenders[enLoadingPhase_First].Init("Assets/sprite/neonNormalStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_First].SetPosition({ -319.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_Second].Init("Assets/sprite/neonGreenStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_Second].SetPosition({ -193.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_Third].Init("Assets/sprite/neonBlueStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_Third].SetPosition({ -65.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_Fourth].Init("Assets/sprite/neonPurpleStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_Fourth].SetPosition({ 64.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_Fifth].Init("Assets/sprite/neonOrangeStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_Fifth].SetPosition({ 190.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_Sixth].Init("Assets/sprite/neonRedStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_Sixth].SetPosition({ 317.0f, -393.5f, 0.0f });

	for (auto& sprite : m_LoadingPhaseSpriteRenders)
	{
		sprite.Update();
	}

	return true;
}

void LoadingView::Update()
{
	if (showLoadingPhases[enLoadingPhase_Sixth])
	{
		SetTextOption(FONT_POSITION.x, -FONT_POSITION.y, FONT_SIZE, FONT_COLOR, &m_pushA_FontRender, L"PUSH (A) ");

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_SelectSE);

			DeleteGO(this);
		}
	}
}


void LoadingView::Render(RenderContext& rc)
{
	m_LoadingSceneSpriteRender.Draw(rc);

	for (int i = 0; i < Phase_Num; i++)
	{
		if (showLoadingPhases[i])
		{
			m_LoadingPhaseSpriteRenders[i].Draw(rc);
		}
	}

	m_pushA_FontRender.Draw(rc);
}