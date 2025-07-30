#include "stdafx.h"
#include "LoadingView.h"
#include "SoundManager.h"
#include "Tutorial.h"
#include "Type.h"
#include "SpriteManager.h"

namespace
{
	const Vector4 FONT_COLOR = { 0.9f, 0.9f, 1.0f, 1.0f };	// 青みがかった白。
	const Vector2 FONT_POSITION = { 450.0f, -350.0f };		// PUSH(A)の位置。
	const float FONT_SIZE = 2.0f;							// PUSH(A)のサイズ。

	/// <summary>
	/// ロード画面の星の位置を表す3次元ベクトルの定数配列です。
	/// </summary>
	const Vector3 LOADING_VIEW_STAR_POSITIONS[] =
	{
		{-319.0f, -393.5f,0.0f},	// 1。
		{-193.0f, -393.5f,0.0f},	// 2。
		{-65.0f, -393.5f,0.0f},		// 3。
		{64.0f, -393.5f,0.0f},		// 4。
		{190.0f, -393.5f,0.0f},		// 5。
		{317.0f, -393.5f,0.0f}		// 6。
	};
}

LoadingView::~LoadingView()
{
	NewGO<Tutorial>(0, "tutorial");
}

bool LoadingView::Start()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");

	spriteManager->SpriteInit(m_LoadingSceneSpriteRender, enSpriteKinds_LoadingView);

	for (int i = 0; i < enLoadingPhase_Num; i++)
	{
		// SpriteManagerではenumが2から始まっているため、Phase数を加算する。
		spriteManager->SpriteInit(m_LoadingPhaseSpriteRenders[i], enSpriteKinds_NeonNormalStar + i);
		m_LoadingPhaseSpriteRenders[i].SetPosition(LOADING_VIEW_STAR_POSITIONS[i]);
		m_LoadingPhaseSpriteRenders[i].Update();
	}

	return true;
}

void LoadingView::Update()
{
	if (showLoadingPhases[enLoadingPhase_Sixth])
	{
		SetTextOption(FONT_POSITION.x, FONT_POSITION.y, FONT_SIZE, FONT_COLOR, &m_pushA_FontRender, L"PUSH (A) ");

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

	for (int i = 0; i < enLoadingPhase_Num; i++)
	{
		if (showLoadingPhases[i])
		{
			m_LoadingPhaseSpriteRenders[i].Draw(rc);
		}
	}

	m_pushA_FontRender.Draw(rc);
}