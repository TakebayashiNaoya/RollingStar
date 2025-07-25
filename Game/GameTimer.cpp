#include "stdafx.h"
#include "GameTimer.h"
#include "Game.h"
#include "Type.h"

namespace
{
	const Vector2 FONT_POSITION = { -200.0f,500.0f };		// フォントのポジション。
	const float FONT_SCALE = 1.5f;							// フォントのサイズ。
	const float COLOR_CHANGE_TIME = 30.0f;					// 残りタイムがこの定数を下回ったとき、表示されている残り時間の色が変化します。
	const float MAX_TIMER = 60.0f;							// 制限時間を設定します。
	const Vector4 g_vec4Red = { 1.0f, 0.0f, 0.0f, 0.0f };	// フォントを赤色にするためのRBGA値です。
}

bool GameTimer::Start()
{
	m_game = FindGO<Game>("game");
	return true;
}

void GameTimer::Update()
{
	if (m_game->GetGameStartFlag())
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
		m_timeLimit = MAX_TIMER - m_timer;

		SetTextOption(FONT_POSITION.x, FONT_POSITION.y, FONT_SCALE, g_vec4White, &m_timeLimitfontRender,
			L"のこりタイム\n　%d/%d秒", int(m_timeLimit), int(MAX_TIMER));

		// 途中で時間を赤色にしてプレイヤーを急かします。
		if (m_timeLimit < COLOR_CHANGE_TIME)
		{
			m_timeLimitfontRender.SetColor(g_vec4Red);
		}
	}
}

void GameTimer::Render(RenderContext& rc)
{
	if (m_game->GetGameStartFlag())
	{
		m_timeLimitfontRender.Draw(rc);
	}
}
