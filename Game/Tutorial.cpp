#include "stdafx.h"
#include "Tutorial.h"
#include "GameTimer.h"
#include "Game.h"
#include "CountDown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{
	m_countDown = NewGO<CountDown>(0, "countdown");
}

bool Tutorial::Start()
{
	m_spriteRender.Init("Assets/sprite/backBlack.dds", 1280.0f, 800.0f);//黒背景
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE

	m_game = NewGO<Game>(0, "game");
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	return true;
}

void Tutorial::Update()
{
	//チュートリアル表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"　　　　【遊び方】\n\n月の上の走りまわり\n\nすべてのスターを集めましょう！\n\nスターは全部で%d個あります。\n\n制限時間は%d秒です。\n\n（A）を押してスタート！", m_game->m_starSum, int(m_gameTimer->m_maxTimer));
	m_fontRender.SetText(wcsbuf);						//描画する。
	m_fontRender.SetScale(1.5f);						//文字のサイズ
	m_fontRender.SetPosition({ -480.0f,350.0f,0.0f });	//表示する座標を設定する。
	m_fontRender.SetColor(g_vec4White);					//表示する色を設定する。

	//Aを押してスタート
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

void Tutorial::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}