#include "stdafx.h"
#include "Score.h"
#include"Star.h"
#include"Game.h"

Score::Score()
{

}

Score::~Score()
{

}

bool Score::Start()
{
	m_star = FindGO<Star>("star");
	m_game = FindGO<Game>("game");
	return true;
}

void Score::Update()
{
	if (m_game->m_gameEndFlag == true)
	{
		return;
	}
	if (m_game->m_gameStartFlag == false)
	{
		return;
	}

	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"スター\n%d/%d", m_counter, m_game->m_starSum);

	m_fontRender.SetText(wcsbuf);

	//表示する座標を設定する。
	m_fontRender.SetPosition({ 400.0f,500.0f,0.0f });

	//文字のサイズ
	m_fontRender.SetScale(1.5f);

	//表示する色を設定する。
	m_fontRender.SetColor(g_vec4Yellow);
}

void Score::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		//スコアを描画する。
		m_fontRender.Draw(rc);
	}
}