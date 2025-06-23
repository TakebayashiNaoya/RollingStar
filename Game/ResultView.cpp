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

ResultView::ResultView()
{

}

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_backSpriteRender.Init("Assets/sprite/backBlack.dds", 1280.0f, 720.0f);
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/result.wav");	//歓声SE
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/end.wav");		//終了サウンド

	m_spriteRender = &m_endSpriteRender;

	/*m_backGround = FindGO<BackGround>("background");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");
	m_star = FindGO<Star>("star");*/

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

		finishCount += g_gameTime->GetFrameDeltaTime();

		if (finishCount >= 3.0f) {
			m_spriteState = 1;
		}

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

			//リザルト表示
			wchar_t wcsbuf[256];
			swprintf_s(wcsbuf, 256, L"　　　【結果】\n\n　 のこりタイム　%d秒\n\n　 集めたスター　%d/%d\n\n（A）を押してタイトルへ", int(m_gameTimer->m_timeLimit), m_score->m_counter, m_game->m_starSum);
			m_fontRender.SetText(wcsbuf);						//描画する。
			m_fontRender.SetScale(2.0f);						//文字のサイズ
			m_fontRender.SetPosition({ -550.0f,300.0f,0.0f });	//表示する座標を設定する。
			m_fontRender.SetColor(g_vec4White);					//表示する色を設定する。

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
		m_fontRender.Draw(rc);
	}
}