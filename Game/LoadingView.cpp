#include "stdafx.h"
#include "LoadingView.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "Tutorial.h"
#include "Type.h"

LoadingView::LoadingView()
{
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");//ボタンSE
}

LoadingView::~LoadingView()
{
	NewGO<Tutorial>(0, "tutorial");
}

bool LoadingView::Start()
{
	m_LoadingSceneSpriteRender.Init("Assets/sprite/LoadingView.dds", 1920.0f, 1080.0f);

	m_LoadingPhaseSpriteRenders[enLoadingPhase_1].Init("Assets/sprite/neonNormalStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_1].SetPosition({ -319.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_2].Init("Assets/sprite/neonGreenStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_2].SetPosition({ -193.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_3].Init("Assets/sprite/neonBlueStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_3].SetPosition({ -65.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_4].Init("Assets/sprite/neonPurpleStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_4].SetPosition({ 64.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_5].Init("Assets/sprite/neonOrangeStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_5].SetPosition({ 190.0f, -393.5f, 0.0f });

	m_LoadingPhaseSpriteRenders[enLoadingPhase_6].Init("Assets/sprite/neonRedStar.dds", 120.0f, 120.0f);
	m_LoadingPhaseSpriteRenders[enLoadingPhase_6].SetPosition({ 317.0f, -393.5f, 0.0f });

	for (int i = 0; i < Phase_Num; i++)
	{
		m_LoadingPhaseSpriteRenders[i].Update();
	}

	return true;
}

void LoadingView::Update()
{
	if (showLoadingPhases[enLoadingPhase_6])
	{
		SetTextOption(450.0f, -350.0f, 2.0f, { 0.9f, 0.9f, 1.0f, 1.0f }, &m_pushA_FontRender, L"PUSH (A) ");

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
}


void LoadingView::Render(RenderContext& rc)
{
	m_LoadingSceneSpriteRender.Draw(rc);

	for (int i = 0; i < Phase_Num; i++) {
		if (showLoadingPhases[i]) {
			m_LoadingPhaseSpriteRenders[i].Draw(rc);
		}
	}

	m_pushA_FontRender.Draw(rc);
}