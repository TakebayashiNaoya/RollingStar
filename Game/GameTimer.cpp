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

	//�Q�[�������Ԃ��擾
	m_timer += g_gameTime->GetFrameDeltaTime();

	m_timeLimit = m_maxTimer - m_timer;

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"�̂���^�C��\n�@%d/%d�b", int(m_timeLimit), int(m_maxTimer));

	//�`�悷��B
	m_fontRender.SetText(wcsbuf);

	//�\��������W��ݒ肷��B
	m_fontRender.SetPosition({ -200.0f,500.0f,0.0f });

	//�\������F��ݒ肷��B
	if (m_timeLimit > 30)
	{
		m_fontRender.SetColor(g_vec4White);
	}
	else
	{
		//�^�C�����~�b�g��30�b�ɂȂ�����ԐF�ɂȂ�
		const Vector4 g_vec4Red = { 1.0f, 0.0f, 0.0f, 0.0f };//�ԐF�����
		m_fontRender.SetColor(g_vec4Red);
	}

	//�����̃T�C�Y
	m_fontRender.SetScale(1.5f);


}

void GameTimer::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		//�X�R�A��`�悷��B
		m_fontRender.Draw(rc);
	}
}
