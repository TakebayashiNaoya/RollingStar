#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "LoadingView.h"

Title::Title()
{

}

Title::~Title()
{
	//BGMを止める
	DeleteGO(m_titleBgm);

	//インゲームへ
	m_game = NewGO<Game>(0, "game");
}

bool Title::Start()
{
	m_spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);	//タイトル画像読み込み
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");		//タイトルBGM
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//ボタンSE

	//BGMを流す
	m_titleBgm = NewGO<SoundSource>(0);
	m_titleBgm->Init(0);
	m_titleBgm->Play(true);//ループ再生

	return true;
}

void Title::Update()
{
	//PUSH STARTの表示
	m_fontRender.SetText(L"PUSH (A) START");				//文字を設定する。
	m_fontRender.SetPosition({ -470.0f,-200.0f,0.0f });	//表示する座標を設定する。
	m_fontRender.SetScale(3.0f);						//文字のサイズ
	m_fontRender.SetColor(g_vec4Yellow);				//表示する色を設定する。

	switch (m_titleStep)
	{
	case Title::enTitleStep_1:
		//Aを押したら終了
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//ボタンSE
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(3.5f);

			//ロード画面を表示
			NewGO<LoadingView>(0, "loadingview");

			m_titleStep = enTitleStep_2;
		}
		break;
	case Title::enTitleStep_2:
		//1フレーム待つため
		m_titleStep = enTitleStep_3;
		break;
	case Title::enTitleStep_3:
		DeleteGO(this);
		break;
	default:
		break;
	}


}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}