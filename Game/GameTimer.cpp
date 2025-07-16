#include "stdafx.h"
#include "GameTimer.h"

#include "Game.h"
#include "Type.h"

namespace {
	const float COLOR_CHANGE_TIME = 30.0f;
	const float MAX_TIMER = 60.0f;
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

		SetTextOption(-200.0f, 500.0f, 1.5f, g_vec4White, &m_timeLimitfontRender, L"のこりタイム\n　%d/%d秒", int(m_timeLimit), int(MAX_TIMER));

		//途中で時間を赤色にしてプレイヤーを急かす
		if (m_timeLimit < COLOR_CHANGE_TIME) {
			m_timeLimitfontRender.SetColor({ 1.0f, 0.0f, 0.0f, 0.0f });
		}
	}
}

void GameTimer::Render(RenderContext& rc)
{
	if (m_game->GetGameStartFlag()) {
		m_timeLimitfontRender.Draw(rc);
	}
}
