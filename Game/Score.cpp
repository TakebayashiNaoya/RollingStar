#include "stdafx.h"
#include "Score.h"
#include "Game.h"
#include "Star.h"
#include "SpriteManager.h"

namespace
{
	const Vector2 SCORE_TEXT_VIEW_POSITION = { 400.0f, 500.0f };
	const float SCORE_TEXT_VIEW_SCALE = 1.5f;

	const Vector2 STAR_COUNT_VIEW_POSITION[enStarKinds_Num] =
	{
		{-850.0f,420.0f},
		{-850.0f,370.0f},
		{-850.0f,320.0f},
		{-850.0f,270.0f},
		{-850.0f,220.0f},
		{-850.0f,170.0f}
	};
	const float STAR_COUNT_VIEW_SCALE = 1.3f;

	const Vector2 TOTAL_SCORE_FONT_POSITION = { 410.0f, 430.0f };
	const float TOTAL_SCORE_FONT_SCALE = 1.5f;

	const Vector3 STAR_SPRITE_SCALE[enStarKinds_Num] =
	{
		{ -900.0f,400.0f,0.0f },
		{ -900.0f,350.0f,0.0f },
		{ -900.0f,300.0f,0.0f },
		{ -900.0f,250.0f,0.0f },
		{ -900.0f,200.0f,0.0f },
		{ -900.0f,150.0f,0.0f },
	};
}

bool Score::Start()
{
	m_star = FindGO<Star>("star");
	m_game = FindGO<Game>("game");

	SpriteRenderList();

	SetTextOption(SCORE_TEXT_VIEW_POSITION.x, SCORE_TEXT_VIEW_POSITION.y,
		SCORE_TEXT_VIEW_SCALE, g_vec4Yellow, &m_scoreFontRender, L"スコア");

	return true;
}

void Score::Update()
{
	/// <summary>
	/// チュートリアル～リザルトの間、常にステージとプレイヤーは表示する。
	/// インゲーム（スタート～終了）の間だけスコアを表示するためにフラグで管理する。
	/// </summary>
	if (!m_game->GetGameStartFlag())
	{
		return;
	}

	TotalScoreCalc();

	/// <summary>
	/// 合計スコアのフォントレンダーを設定。
	/// </summary>
	SetTextOption(TOTAL_SCORE_FONT_POSITION.x, TOTAL_SCORE_FONT_POSITION.y,
		TOTAL_SCORE_FONT_SCALE, g_vec4Yellow, &m_totalScoreFontRender, L"%d", m_totalScore);

	/// <summary>
	/// 各種スターの取得数のフォントレンダーを設定。
	/// </summary>
	for (int i = 0; i < enStarKinds_Num; i++)
	{
		SetTextOption(STAR_COUNT_VIEW_POSITION[i].x, STAR_COUNT_VIEW_POSITION[i].y,
			STAR_COUNT_VIEW_SCALE, g_vec4White, &m_getStarCountFontRender[i], L"%d", m_starCount[i]);
	}

}

void Score::Render(RenderContext& rc)
{
	/// <summary>
	/// チュートリアル～リザルトの間、常にステージとプレイヤーは表示する。
	/// インゲーム（スタート～終了）の間だけスコアを表示するためにフラグで管理する。
	/// </summary>
	if (!m_game->GetGameStartFlag())
	{
		return;
	}

	m_scoreFontRender.Draw(rc);
	m_totalScoreFontRender.Draw(rc);

	for (FontRender& getStarCount : m_getStarCountFontRender)
	{
		getStarCount.Draw(rc);
	}

	for (SpriteRender& star : m_starSpriteRender)
	{
		star.Draw(rc);
	}
}

/// <summary>
/// スプライトレンダーまとめ
/// </summary>
void Score::SpriteRenderList()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");

	for (int i = 0; i < enStarKinds_Num; i++)
	{
		spriteManager->SpriteInit(m_starSpriteRender[i], enSpriteKinds_RedStar + i);
		m_starSpriteRender[i].SetPosition(STAR_SPRITE_SCALE[i]);
		m_starSpriteRender[i].Update();
	}
}

void Score::TotalScoreCalc()
{
	m_totalScore = m_starCount[enStarKinds_Red] * RED_STAR_POINT
		+ m_starCount[enStarKinds_Orange] * ORANGE_STAR_POINT
		+ m_starCount[enStarKinds_Purple] * PURPLE_STAR_POINT
		+ m_starCount[enStarKinds_Blue] * BLUE_STAR_POINT
		+ m_starCount[enStarKinds_Green] * GREEN_STAR_POINT
		+ m_starCount[enStarKinds_Normal] * NORMAL_STAR_POINT;
}
