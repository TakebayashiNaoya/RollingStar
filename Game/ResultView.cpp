#include "stdafx.h"
#include "ResultView.h"
#include "BackGround.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "Player.h"
#include "Score.h"
#include "Star.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SaveData.h"
#include <algorithm>

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

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/result.wav");	//歓声SE
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/end.wav");		//終了サウンド

	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_score = FindGO<Score>("score");

	m_saveData = FindGO<SaveData>("savedata");

	return true;
}

//更新処理。

void ResultView::Update()
{
	if (m_isFlag == true)
	{
		switch (m_viewState)
		{
		case enViewStates_GameEnd:

			m_spriteRender = &m_endSpriteRender;

			//1回だけ終了サウンドを鳴らす
			if (endState == 0)
			{
				EndSE();
				endState = 1;
			}

			//タイムアップから3秒後にリザルト表示
			m_timerToResult += g_gameTime->GetFrameDeltaTime();
			if (m_timerToResult >= 3.0f) {
				m_viewState = enViewStates_Result;
			}

			break;

		case enViewStates_Result:

			m_spriteRender = &m_resultSpriteRender;

			SetScoreFontRender();

			//1回だけ歓声SEを鳴らす
			if (callState == 0) {
				CallSE();
				callState = 1;
			}

			if (g_pad[0]->IsTrigger(enButtonA)) {
				TriggerSE();

				m_viewState = enViewStates_Rankings;
			}

			break;

		case enViewStates_Rankings:

			m_spriteRender = &m_backScreenSpriteRender;

			//一度だけセーブする
			if (saveState == 0) {
				m_saveData->m_scoreRankList.push_back(m_score->m_totalScore);
				saveState = 1;
			}

			std::sort(m_saveData->m_scoreRankList.begin(), m_saveData->m_scoreRankList.end(), [](int a, int b) {return a > b; });

			SetScoreOfRankFontRenderList();

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				TriggerSE();

				m_title = NewGO<Title>(0, "title");

				DeleteGO(this);
			}

		}
	}
}

//描画処理。
void ResultView::Render(RenderContext& rc)
{
	if (m_isFlag == true)
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


void ResultView::RankingUI_InitSetList()
{
	//ランキングで表示するUI
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

void ResultView::SetScoreFontRender()
{
	SetTotalScoreFontRender();
	SetGotStarCountFontRender();
}

void ResultView::SetTotalScoreFontRender()
{
	//合計スコア表示
	wchar_t tmp[256];
	swprintf_s(tmp, 256, L"%d", m_score->m_totalScore);
	m_totalScoreFontRender.SetText(tmp);
	m_totalScoreFontRender.SetPosition({ -250.0f,230.0f ,0.0f });
	m_totalScoreFontRender.SetScale(4.0f);
	m_totalScoreFontRender.SetColor(g_vec4White);
}

void ResultView::SetGotStarCountFontRender()
{
	/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
	FontOption text[StarKinds_Num];
	text[enStarKinds_Red] = { m_score->m_starCount[enStarKinds_Red],410.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Orange] = { m_score->m_starCount[enStarKinds_Orange],0.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Purple] = { m_score->m_starCount[enStarKinds_Purple],-360.0f,-160.0f,2.0f,g_vec4White };
	text[enStarKinds_Blue] = { m_score->m_starCount[enStarKinds_Blue],410.0f,-20.0f,2.0f,g_vec4White };
	text[enStarKinds_Green] = { m_score->m_starCount[enStarKinds_Green],0.0f,-20.0f,2.0f,g_vec4White };
	text[enStarKinds_Normal] = { m_score->m_starCount[enStarKinds_Normal],-360.0f,-20.0f,2.0f,g_vec4White };

	for (int i = 0; i < StarKinds_Num; i++)
	{
		wchar_t tmp[256];
		swprintf_s(tmp, 256, L"%d", text[i].data);
		m_gotStarCountFontRenderList[i].SetText(tmp);
		m_gotStarCountFontRenderList[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0.0f });
		m_gotStarCountFontRenderList[i].SetScale(text[i].scale);
		m_gotStarCountFontRenderList[i].SetColor(text[i].textColor);
	}
}

void ResultView::SetScoreOfRankFontRenderList()
{
	wchar_t getScore1st[256];
	swprintf_s(getScore1st, 256, L"%d", m_saveData->m_scoreRankList[enRanking_1st]);
	m_scoreOfRankFontRenderList[enRanking_1st].SetText(getScore1st);
	m_scoreOfRankFontRenderList[enRanking_1st].SetScale(2.0f);
	m_scoreOfRankFontRenderList[enRanking_1st].SetPosition({ -120.0f,220.0f,0.0f });

	wchar_t getScore2nd[256];
	swprintf_s(getScore2nd, 256, L"%d", m_saveData->m_scoreRankList[enRanking_2nd]);
	m_scoreOfRankFontRenderList[enRanking_2nd].SetText(getScore2nd);
	m_scoreOfRankFontRenderList[enRanking_2nd].SetScale(2.0f);
	m_scoreOfRankFontRenderList[enRanking_2nd].SetPosition({ -120.0f,20.0f,0.0f });

	wchar_t getScore3rd[256];
	swprintf_s(getScore3rd, 256, L"%d", m_saveData->m_scoreRankList[enRanking_3rd]);
	m_scoreOfRankFontRenderList[enRanking_3rd].SetText(getScore3rd);
	m_scoreOfRankFontRenderList[enRanking_3rd].SetScale(2.0f);
	m_scoreOfRankFontRenderList[enRanking_3rd].SetPosition({ -120.0f,-180.0f,0.0f });

	if (m_saveData->m_scoreRankList[enRanking_1st] == m_score->m_totalScore) {
		m_scoreOfRankFontRenderList[enRanking_1st].SetColor(g_vec4Yellow);
	}
	else if (m_saveData->m_scoreRankList[enRanking_2nd] == m_score->m_totalScore) {
		m_scoreOfRankFontRenderList[enRanking_2nd].SetColor(g_vec4Yellow);
	}
	else if (m_saveData->m_scoreRankList[enRanking_3rd] == m_score->m_totalScore) {
		m_scoreOfRankFontRenderList[enRanking_3rd].SetColor(g_vec4Yellow);
	}
}

void ResultView::EndSE()
{
	SoundSource* endSE = NewGO<SoundSource>(0);
	endSE->Init(5);
	endSE->Play(false);
	endSE->SetVolume(3.5f);
}

void ResultView::CallSE()
{
	SoundSource* callSE = NewGO<SoundSource>(0);
	callSE->Init(7);
	callSE->Play(false);
	callSE->SetVolume(3.5f);
}

void ResultView::TriggerSE()
{
	SoundSource* triggerSE = NewGO<SoundSource>(0);
	triggerSE->Init(6);
	triggerSE->Play(false);
	triggerSE->SetVolume(3.5f);
}

