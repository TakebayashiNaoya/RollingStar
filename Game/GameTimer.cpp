#include "stdafx.h"
#include "GameTimer.h"
#include "Game.h"

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

bool GameTimer::Start()
{
	m_game = FindGO<Game>("game");
	return true;
}

void GameTimer::Update()
{
	if (m_game->m_gameEndFlag == true) {
		return;
	}

	if (m_game->m_gameStartFlag == false) {
		return;
	}

	//ゲーム内時間を取得
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_timeLimit = m_maxTimer - m_timer;

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"のこりタイム\n　%d/%d秒", int(m_timeLimit), int(m_maxTimer));

	//描画する。
	m_fontRender.SetText(wcsbuf);

	//表示する座標を設定する。
	m_fontRender.SetPosition({ -200.0f,500.0f,0.0f });

	//表示する色を設定する。
	if (m_timeLimit > 30)
	{
		m_fontRender.SetColor(g_vec4White);
	}
	else
	{
		//タイムリミットが30秒になったら赤色になる
		const Vector4 g_vec4Red = { 1.0f, 0.0f, 0.0f, 0.0f };//赤色を作る
		m_fontRender.SetColor(g_vec4Red);
	}

	//文字のサイズ
	m_fontRender.SetScale(1.5f);


}

void GameTimer::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		//スコアを描画する。
		m_fontRender.Draw(rc);
	}
}
