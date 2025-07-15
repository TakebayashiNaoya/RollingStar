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

namespace {
	const float FONT_SPACE = -200.0f;
}

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	//spriteRenderに入れて切り替え
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_resultSpriteRender.Init("Assets/sprite/result.dds", 1280.0f, 900.0f);
	m_backScreenSpriteRender.Init("Assets/sprite/backBlack.dds", 1280.0f, 900.0f);
	m_spriteRender = &m_endSpriteRender;

	RankingUI_InitSetList();

	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_score = FindGO<Score>("score");
	m_saveData = FindGO<SaveData>("savedata");

	return true;
}

//更新処理。

void ResultView::Update()
{
	if (m_game->GetGameEndFlag())
	{
		switch (m_viewState)
		{
		case enViewStates_GameEnd:

			m_spriteRender = &m_endSpriteRender;

			//1回だけ終了サウンドを鳴らす
			if (onceEndSE)
			{
				SoundNewGO(enSoundList_EndSE);
				onceEndSE = false;
			}

			//タイムアップから3秒後にリザルト表示
			m_timerToResult += g_gameTime->GetFrameDeltaTime();
			if (m_timerToResult >= 3.0f) {
				m_viewState = enViewStates_Result;
			}

			break;

		case enViewStates_Result:

			m_spriteRender = &m_resultSpriteRender;

			SetTotalScoreFontRender();
			SetGotStarCountFontRender();

			//1回だけ歓声SEを鳴らす
			if (onceCallSE) {
				SoundNewGO(enSoundList_CallSE);
				onceCallSE = false;
			}

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				SoundNewGO(enSoundList_SelectSE);

				m_viewState = enViewStates_Rankings;
			}

			break;

		case enViewStates_Rankings:

			m_spriteRender = &m_backScreenSpriteRender;

			//一度だけセーブする
			if (onceSaveScore) {
				m_saveData->m_scoreRankList.push_back(m_score->GetTotalScore());
				onceSaveScore = false;
			}

			std::sort(m_saveData->m_scoreRankList.begin(), m_saveData->m_scoreRankList.end(), [](int a, int b) {return a > b; });

			SetScoreOfRankFontRenderList();

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				SoundNewGO(enSoundList_SelectSE);

				m_title = NewGO<Title>(0, "title");

				DeleteGO(this);
			}

		}
	}
}

//描画処理。
void ResultView::Render(RenderContext& rc)
{
	if (m_game->GetGameEndFlag())
	{
		m_spriteRender->Draw(rc);

		switch (m_viewState)
		{
		case enViewStates_Result:

			m_totalScoreFontRender.Draw(rc);

			for (int i = 0; i < StarKinds_Num; i++) {
				m_gotStarCountFontRenderList[i].Draw(rc);
			}
			break;

		case enViewStates_Rankings:

			for (int i = 0; i < SpritesForRankingView_Num; i++) {
				m_spritesForRankingView[i].Draw(rc);
			}

			for (int i = 0; i < Ranking_Num; i++) {
				m_scoreOfRankFontRenderList[i].Draw(rc);
			}
		}
	}
}

//ランキングで表示するUI
void ResultView::RankingUI_InitSetList()
{
	m_spritesForRankingView[enSpritesForRankingView_Ranking].Init("Assets/sprite/ranking.dds", 500.0f, 100.0f);
	m_spritesForRankingView[enSpritesForRankingView_Ranking].SetPosition({ 0.0f,350.0f,0.0f });

	m_spritesForRankingView[enSpritesForRankingView_GoldCrown].Init("Assets/sprite/goldCrown.dds", 100.0f, 100.0f);
	m_spritesForRankingView[enSpritesForRankingView_GoldCrown].SetPosition({ -300.0f,180.0f,0.0f });

	m_spritesForRankingView[enSpritesForRankingView_SilverCrown].Init("Assets/sprite/silverCrown.dds", 100.0f, 100.0f);
	m_spritesForRankingView[enSpritesForRankingView_SilverCrown].SetPosition({ -300.0f,-20.0f,0.0f });

	m_spritesForRankingView[enSpritesForRankingView_BronzeCrown].Init("Assets/sprite/bronzeCrown.dds", 100.0f, 100.0f);
	m_spritesForRankingView[enSpritesForRankingView_BronzeCrown].SetPosition({ -300.0f,-220.0f,0.0f });

	m_spritesForRankingView[enSpritesForRankingView_PushA].Init("Assets/sprite/pushAtoTitle.dds", 600.0f, 100.0f);
	m_spritesForRankingView[enSpritesForRankingView_PushA].SetPosition({ 300.0f,-400.0f,0.0f });

	for (int i = 0; i < SpritesForRankingView_Num; i++) {
		m_spritesForRankingView[i].Update();
	}
}

void ResultView::SetTotalScoreFontRender()
{
	SetTextOption(-250.0f, 230.0f, 4.0f, g_vec4White, &m_totalScoreFontRender, L"%d", m_score->GetTotalScore());
}

void ResultView::SetGotStarCountFontRender()
{
	/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
	FontOption text[StarKinds_Num];
	text[enStarKinds_Red] = { m_score->GetStarCount(enStarKinds_Red),410.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Orange] = { m_score->GetStarCount(enStarKinds_Orange),0.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Purple] = { m_score->GetStarCount(enStarKinds_Purple),-360.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Blue] = { m_score->GetStarCount(enStarKinds_Blue),410.0f,-20.0f,2.0f,g_vec4White };
	text[enStarKinds_Green] = { m_score->GetStarCount(enStarKinds_Green),0.0f,-20.0f,2.0f,g_vec4White };
	text[enStarKinds_Normal] = { m_score->GetStarCount(enStarKinds_Normal),-360.0f,-20.0f,2.0f,g_vec4White };

	for (int i = 0; i < StarKinds_Num; i++)
	{
		SetTextOption(text[i].pos_x, text[i].pos_y, text[i].scale, text[i].textColor, &m_gotStarCountFontRenderList[i], L"%d", text[i].data);
	}
}

void ResultView::SetScoreOfRankFontRenderList()
{
	for (int i = 0; i < Ranking_Num; i++) {
		SetTextOption(-120.0f, 220.0f + FONT_SPACE * i, 2.0f, g_vec4White, &m_scoreOfRankFontRenderList[i], L"%d", m_saveData->m_scoreRankList[i]);
	}

	for (int i = 0; i < Ranking_Num; i++)
	{
		if (m_saveData->m_scoreRankList[i] == m_score->GetTotalScore())
		{
			m_scoreOfRankFontRenderList[i].SetColor(g_vec4Yellow);
			break;
		}
	}
}
