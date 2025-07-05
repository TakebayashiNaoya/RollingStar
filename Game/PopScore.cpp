#include "stdafx.h"
#include "PopScore.h"
#include "Score.h"
#include "Star.h"
#include "Type.h"
#include "PopScoreManager.h"

namespace {
	float const MOVE_SPEED = 150.0f;
}

PopScore::PopScore()
{
}

PopScore::~PopScore()
{
}

bool PopScore::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");

	switch (m_popScoreManager->colorChecker)
	{
	case enStarColorType_Red:
		m_setPoint = RED_STAR_POINT;
		m_setColor = { 1.0f,0.0f,0.0f,1.0f };
		m_setScale = 2.0f;
		m_setPos = { -140.0f,80.0f };
		break;
	case enStarColorType_Orange:
		m_setPoint = ORANGE_STAR_POINT;
		m_setColor = { 1.0f,0.5f,0.0f,1.0f };
		m_setScale = 1.9f;
		m_setPos = { -115.0f,80.0f };
		break;
	case enStarColorType_Purple:
		m_setPoint = PURPLE_STAR_POINT;
		m_setColor = { 1.0f,0.0f,1.0f,1.0f };
		m_setScale = 1.8f;
		m_setPos = { -110.0f,80.0f };
		break;
	case enStarColorType_Blue:
		m_setPoint = BLUE_STAR_POINT;
		m_setColor = { 0.0f,0.0f,1.0f,1.0f };
		m_setScale = 1.7f;
		m_setPos = { -105.0f,80.0f };
		break;
	case enStarColorType_Green:
		m_setPoint = GREEN_STAR_POINT;
		m_setColor = { 0.0f,1.0f,0.0f,1.0f };
		m_setScale = 1.6f;
		m_setPos = { -100.0f,80.0f };
		break;
	case enStarColorType_Normal:
		m_setPoint = NORMAL_STAR_POINT;
		m_setColor = { 1.0f,1.0f,0.0f,1.0f };
		m_setScale = 1.5f;
		m_setPos = { -70.0f,80.0f };
		break;
	}

	wchar_t tmp2[256];
	swprintf_s(tmp2, 256, L"+%d", m_setPoint);
	m_popScoreFontRender.SetText(tmp2);			//テキスト表示
	m_popScoreFontRender.SetScale(m_setScale);	//サイズ

	return true;
}

void PopScore::Update()
{
	//フェードアウト時間の計測
	m_fadeTimer += g_gameTime->GetFrameDeltaTime();

	//座標の計算（zは0）
	m_popScoreFontRender.SetPosition(m_setPos.x, m_setPos.y + m_fadeTimer * MOVE_SPEED, 0.0f);

	//色の計算・設定
	FadingColorCalc();
	m_popScoreFontRender.SetColor(m_fadingColor);

	if (m_fadeTimer >= m_fadeDuration) {
		DeleteGO(this);
	}
}

void PopScore::Render(RenderContext& rc)
{
	m_popScoreFontRender.Draw(rc);
}

//フェードアウトの色計算
void PopScore::FadingColorCalc()
{
	m_fadingColor.r = m_setColor.r * (1 - m_fadeTimer / m_fadeDuration);
	m_fadingColor.b = m_setColor.b * (1 - m_fadeTimer / m_fadeDuration);
	m_fadingColor.g = m_setColor.g * (1 - m_fadeTimer / m_fadeDuration);
	m_fadingColor.a = m_setColor.a * (1 - m_fadeTimer / m_fadeDuration);
}
