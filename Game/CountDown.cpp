#include "stdafx.h"
#include "CountDown.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

CountDown::CountDown()
{
	//カウントダウンの画像
	m_count3SpriteRender.Init("Assets/sprite/count3.dds", 1920.0f, 1080.0f);			//カウントダウン3
	m_count2SpriteRender.Init("Assets/sprite/count2.dds", 1920.0f, 1080.0f);			//カウントダウン2
	m_count1SpriteRender.Init("Assets/sprite/count1.dds", 1920.0f, 1080.0f);			//カウントダウン1
	m_countStartSpriteRender.Init("Assets/sprite/countStart.dds", 1920.0f, 1080.0f);	//カウントダウンスタート

	m_spriteRender = &m_count3SpriteRender;

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/countDownStart.wav");//カウントダウン開始の音
}

CountDown::~CountDown()
{
	m_game->m_gameStartFlag = true;
}

bool CountDown::Start()
{
	//カウントダウン開始の音
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(4);
	se->Play(false);
	se->SetVolume(3.5f);

	m_game = FindGO<Game>("game");
	return true;
}

void CountDown::Update()
{
	countDown += g_gameTime->GetFrameDeltaTime();		//秒数カウント

	if (countDown >= 0.0f and countDown < 1.0f) {		//3
		m_spriteRender = &m_count3SpriteRender;
	}
	else if (countDown >= 1.0f and countDown < 2.0f) {	//2
		m_spriteRender = &m_count2SpriteRender;
	}
	else if (countDown >= 2.0f and countDown < 3.0f) {	//1
		m_spriteRender = &m_count1SpriteRender;
	}
	else if (countDown >= 3.0f and countDown < 4.0f) {	//スタート
		m_spriteRender = &m_countStartSpriteRender;
	}
	else if (countDown >= 4.0f) {						//インゲームへ
		DeleteGO(this);
	}

}

void CountDown::Render(RenderContext& rc)
{
	m_spriteRender->Draw(rc);
}