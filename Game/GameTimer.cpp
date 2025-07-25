#include "stdafx.h"
#include "GameTimer.h"
#include "Game.h"
#include "Type.h"

namespace
{
	const Vector2 FONT_POSITION = { -200.0f,500.0f };		// �t�H���g�̃|�W�V�����B
	const float FONT_SCALE = 1.5f;							// �t�H���g�̃T�C�Y�B
	const float COLOR_CHANGE_TIME = 30.0f;					// �c��^�C�������̒萔����������Ƃ��A�\������Ă���c�莞�Ԃ̐F���ω����܂��B
	const float MAX_TIMER = 60.0f;							// �������Ԃ�ݒ肵�܂��B
	const Vector4 g_vec4Red = { 1.0f, 0.0f, 0.0f, 0.0f };	// �t�H���g��ԐF�ɂ��邽�߂�RBGA�l�ł��B
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
			L"�̂���^�C��\n�@%d/%d�b", int(m_timeLimit), int(MAX_TIMER));

		// �r���Ŏ��Ԃ�ԐF�ɂ��ăv���C���[���}�����܂��B
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
