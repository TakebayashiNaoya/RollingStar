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

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_backSpriteRender.Init("Assets/sprite/result.dds", 1280.0f, 900.0f);
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/result.wav");	//歓声SE
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/end.wav");		//終了サウンド

	m_spriteRender = &m_endSpriteRender;

	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_score = FindGO<Score>("score");

	return true;
}

//更新処理。

void ResultView::Update()
{
	if (m_isFlag == true) {

		if (endState == 0) {
			//終了サウンド
			SoundSource* endSE = NewGO<SoundSource>(0);
			endSE->Init(5);
			endSE->Play(false);
			endSE->SetVolume(3.5f);
			endState = 1;	//終了サウンドは1回だけ鳴らす
		}

		//タイムアップから3秒後にリザルト表示
		finishCount += g_gameTime->GetFrameDeltaTime();
		if (finishCount >= 3.0f) { m_spriteState = 1; }

		if (m_spriteState == 0) {
			m_spriteRender = &m_endSpriteRender;
		}
		else if (m_spriteState == 1) {
			m_spriteRender = &m_backSpriteRender;

			//歓声SE
			if (callState == 0) {
				SoundSource* callSE = NewGO<SoundSource>(0);
				callSE->Init(7);
				callSE->Play(false);
				callSE->SetVolume(3.5f);
				callState = 1;	//歓声SEは1回だけ鳴らす
			}

			/// <summary>
			/// フォント設定。
			/// </summary>
			/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
			FontOption text[Font_Num];
			text[totalScore] = { m_score->m_totalScore,-250.0f,230.0f,4.0f,g_vec4White };
			text[redStar] = { m_score->m_redStarCount,410.0f,-160.0f,2.0f,g_vec4White };
			text[orangeStar] = { m_score->m_orangeStarCount,0.0f,-160.0f,2.0f,g_vec4White };
			text[purpleStar] = { m_score->m_purpleStarCount,-360.0f,-160.0f,2.0f,g_vec4White };
			text[blueStar] = { m_score->m_blueStarCount,410.0f,-20.0f,2.0f,g_vec4White };
			text[greenStar] = { m_score->m_greenStarCount,0.0f,-20.0f,2.0f,g_vec4White };
			text[normalStar] = { m_score->m_normalStarCount,-360.0f,-20.0f,2.0f,g_vec4White };

			for (int i = 0; i < Font_Num; i++)
			{
				wchar_t tmp[256];
				swprintf_s(tmp, 256, L"%d", text[i].data);
				m_fontRender[i].SetText(tmp);										//テキスト表示
				m_fontRender[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0 });	//座標
				m_fontRender[i].SetScale(text[i].scale);							//サイズ
				m_fontRender[i].SetColor(text[i].textColor);						//色
			}


			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//ボタンSE
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(6);
				se->Play(false);
				se->SetVolume(3.5f);

				//タイトルへ
				m_title = NewGO<Title>(0, "title");
				//ゲーム終了
				DeleteGO(this);
			}
		}
	}
}

//描画処理。
void ResultView::Render(RenderContext& rc)
{
	if (m_isFlag == true) {
		m_spriteRender->Draw(rc);

		for (int i = 0; i < Font_Num; i++)
		{
			m_fontRender[i].Draw(rc);
		}
	}
}

