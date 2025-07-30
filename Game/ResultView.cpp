#include "stdafx.h"
#include "ResultView.h"
#include "SoundManager.h"
#include "BackGround.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "Player.h"
#include "SaveData.h"
#include "Score.h"
#include "Star.h"
#include "Title.h"
#include <algorithm>
#include "SpriteManager.h"

namespace
{
	const float FONT_SPACE = -200.0f;		// ランキングの1～3位のスコアの表示間隔。
	const float DRAW_SWITCH_DELAY = 3.0f;	// 画面遷移させるまでの時間。

	/// <summary>
	/// この定数はランキングUIの各位置を定義します。
	/// </summary>
	const Vector3 RANKING_UI_POSITION[] =
	{
		{0.0f,350.0f,0.0f},			// 「ランキング」。
		{-300.0f,180.0f,0.0f},		// 金冠。
		{ -300.0f,-20.0f,0.0f },	// 銀冠。
		{ -300.0f,-220.0f,0.0f },	// 銅冠。
		{ 300.0f,-400.0f,0.0f }		// 「Aを押してタイトルへ」。
	};

	const Vector2 TOTAL_SCORE_FONT_POSITION = { -250.0f, 230.0f };	// 合計スコアのフォントを表示する位置。
	const float TOTAL_SCORE_FONT_SCALE = 4.0f;						// 合計スコアのフォントサイズ。

	/// <summary>
	/// スターの獲得数を表示するフォントの各座標を定義します。
	/// </summary>
	const Vector2 GOT_STAR_COUNT_FONT_POSITIONS[] =
	{
		{410.0f,-160.0f},	// レッドスター。
		{0.0f,-160.0f},		// オレンジスター。
		{-360.0f,-160.0f},	// パープルスター。
		{410.0f,-20.0f},	// ブルースター。
		{0.0f,-20.0f},		// グリーンスター。
		{-360.0f,-20.0f}	// ノーマルスター。
	};
	const float GOT_STAR_COUNT_FONT_SCALE = 2.0f;					// スターの獲得数を表示するフォントサイズ。

	const Vector2 RANKING_SCORE_FONT_POSITION = { -120.0f, 220.0f };// ランキングのスコアを表示する位置。
	const float RANKING_SCORE_FONT_SCALE = 2.0f;					// ランキングのスコアのフォントサイズ。
}

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");

	for (int i = 0; i < enViewStates_Num; i++)
	{
		spriteManager->SpriteInit(m_spriteRenders[i], enSpriteKinds_End + i);
	}

	SetupRankingUI();

	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_score = FindGO<Score>("score");
	m_saveData = FindGO<SaveData>("savedata");

	return true;
}

void ResultView::Update()
{
	if (!m_game->GetGameEndFlag())
	{
		return;
	}

	switch (m_viewState)
	{
	case enViewStates_GameEnd:

		// 一度だけ終了サウンドを鳴らします。
		if (onceEndSE)
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_EndSE);
			onceEndSE = false;
		}

		// タイムアップから3秒後にリザルト表示します。
		m_timerToResult += g_gameTime->GetFrameDeltaTime();
		if (m_timerToResult >= DRAW_SWITCH_DELAY)
		{
			m_viewState = enViewStates_Result;
		}

		break;

	case enViewStates_Result:

		SetupTotalScoreFontRender();
		SetupGotStarCountFontRender();

		// 一度だけ歓声SEを鳴らします。
		if (onceCallSE)
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_CallSE);
			onceCallSE = false;
		}

		// Aを押したらランキングビューへ遷移します。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_SelectSE);

			m_viewState = enViewStates_Rankings;
		}

		break;

	case enViewStates_Rankings:

		// 一度だけセーブします。
		if (onceSaveScore)
		{
			m_saveData->m_scoreRankList.push_back(m_score->GetTotalScore());
			onceSaveScore = false;
		}

		// 過去のスコアのセーブデータを昇順にソートします。
		std::sort(m_saveData->m_scoreRankList.begin(), m_saveData->m_scoreRankList.end(), [](int a, int b) {return a > b; });

		SetupScoreOfRankFontRenderList();

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_SelectSE);

			m_title = NewGO<Title>(0, "title");

			DeleteGO(this);
		}
	}
}

void ResultView::Render(RenderContext& rc)
{
	if (!m_game->GetGameEndFlag())
	{
		return;
	}

	m_spriteRender = &m_spriteRenders[m_viewState];
	m_spriteRender->Draw(rc);

	switch (m_viewState)
	{
	case enViewStates_Result:

		m_totalScoreFontRender.Draw(rc);

		for (FontRender& gotStarCount : m_gotStarCountFontRenderList)
		{
			gotStarCount.Draw(rc);
		}
		break;

	case enViewStates_Rankings:

		for (SpriteRender& ui : m_spritesForRankingView)
		{
			ui.Draw(rc);
		}

		for (FontRender& score : m_scoreOfRankFontRenderList)
		{
			score.Draw(rc);
		}
	}
}

void ResultView::SetupRankingUI()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");

	for (int i = 0; i < enSpritesForRankingView_Num; i++)
	{
		spriteManager->SpriteInit(m_spritesForRankingView[i], enSpriteKinds_Ranking + i);
		m_spritesForRankingView[i].SetPosition(RANKING_UI_POSITION[i]);
		m_spritesForRankingView[i].Update();
	}
}

void ResultView::SetupTotalScoreFontRender()
{
	SetTextOption(TOTAL_SCORE_FONT_POSITION.x, TOTAL_SCORE_FONT_POSITION.y, TOTAL_SCORE_FONT_SCALE,
		g_vec4White, &m_totalScoreFontRender, L"%d", m_score->GetTotalScore());
}

void ResultView::SetupGotStarCountFontRender()
{
	for (int i = 0; i < enStarKinds_Num; i++)
	{
		SetTextOption(GOT_STAR_COUNT_FONT_POSITIONS[i].x, GOT_STAR_COUNT_FONT_POSITIONS[i].y,
			GOT_STAR_COUNT_FONT_SCALE, g_vec4White, &m_gotStarCountFontRenderList[i], L"%d", m_score->GetStarCount(i));
	}
}

void ResultView::SetupScoreOfRankFontRenderList()
{
	for (int i = 0; i < enRanking_Num; i++)
	{
		SetTextOption(RANKING_SCORE_FONT_POSITION.x, RANKING_SCORE_FONT_POSITION.y + FONT_SPACE * i,
			RANKING_SCORE_FONT_SCALE, g_vec4White, &m_scoreOfRankFontRenderList[i], L"%d", m_saveData->m_scoreRankList[i]);
	}

	for (int i = 0; i < enRanking_Num; i++)
	{
		if (m_saveData->m_scoreRankList[i] == m_score->GetTotalScore())
		{
			m_scoreOfRankFontRenderList[i].SetColor(g_vec4Yellow);
			break;
		}
	}
}
