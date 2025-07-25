#include "stdafx.h"
#include "PopScore.h"
#include "PopScoreManager.h"
#include "Score.h"
#include "Star.h"
#include "Type.h"

namespace
{
	const float MOVE_SPEED = 150.0f;
	const float FADE_DURATION = 1.0f;

	const Vector2 RED_STARS_SCORE_POP_POSITION = { -140.0f,80.0f };
	const Vector2 ORANGE_STARS_SCORE_POP_POSITION = { -115.0f,80.0f };
	const Vector2 PURPLE_STARS_SCORE_POP_POSITION = { -110.0f,80.0f };
	const Vector2 BLUE_STARS_SCORE_POP_POSITION = { -105.0f,80.0f };
	const Vector2 GREEN_STARS_SCORE_POP_POSITION = { -100.0f,80.0f };
	const Vector2 NORMAL_STARS_SCORE_POP_POSITION = { -70.0f,80.0f };

	const float RED_STARS_POP_SCORE_SCALE = 2.0f;
	const float ORANGE_STARS_POP_SCORE_SCALE = 1.9f;
	const float PURPLE_STARS_POP_SCORE_SCALE = 1.8f;
	const float BLUE_STARS_POP_SCORE_SCALE = 1.7f;
	const float GREEN_STARS_POP_SCORE_SCALE = 1.6f;
	const float NORMAL_STARS_POP_SCORE_SCALE = 1.5f;

	const Vector4 RED_COLOR = { 1.0f,0.0f,0.0f,1.0f };
	const Vector4 ORANGE_COLOR = { 1.0f,0.5f,0.0f,1.0f };
	const Vector4 PURPLE_COLOR = { 1.0f,0.0f,1.0f,1.0f };
	const Vector4 BLUE_COLOR = { 0.0f,0.0f,1.0f,1.0f };
	const Vector4 GREEN_COLOR = { 0.0f,1.0f,0.0f,1.0f };
	const Vector4 NORMAL_COLOR = { 1.0f,1.0f,0.0f,1.0f };
}

bool PopScore::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");

	PopScoreInfo popScoreInfo[StarKinds_Num];
	popScoreInfo[enStarKinds_Red] = { RED_STARS_SCORE_POP_POSITION ,RED_STARS_POP_SCORE_SCALE ,RED_COLOR ,RED_STAR_POINT };
	popScoreInfo[enStarKinds_Orange] = { ORANGE_STARS_SCORE_POP_POSITION ,ORANGE_STARS_POP_SCORE_SCALE ,ORANGE_COLOR ,ORANGE_STAR_POINT };
	popScoreInfo[enStarKinds_Purple] = { PURPLE_STARS_SCORE_POP_POSITION ,PURPLE_STARS_POP_SCORE_SCALE ,PURPLE_COLOR ,PURPLE_STAR_POINT };
	popScoreInfo[enStarKinds_Blue] = { BLUE_STARS_SCORE_POP_POSITION ,BLUE_STARS_POP_SCORE_SCALE ,BLUE_COLOR ,BLUE_STAR_POINT };
	popScoreInfo[enStarKinds_Green] = { GREEN_STARS_SCORE_POP_POSITION ,GREEN_STARS_POP_SCORE_SCALE ,GREEN_COLOR ,GREEN_STAR_POINT };
	popScoreInfo[enStarKinds_Normal] = { NORMAL_STARS_SCORE_POP_POSITION ,NORMAL_STARS_POP_SCORE_SCALE ,NORMAL_COLOR,NORMAL_STAR_POINT };

	SetTextOption(popScoreInfo[m_popScoreManager->GetColorChecker()].popPosition.x,
		popScoreInfo[m_popScoreManager->GetColorChecker()].popPosition.y,
		popScoreInfo[m_popScoreManager->GetColorChecker()].popScale,
		popScoreInfo[m_popScoreManager->GetColorChecker()].popColor,
		&m_popScoreFontRender, L"+%d", popScoreInfo[m_popScoreManager->GetColorChecker()].popPoint);

	m_fadePosition = { popScoreInfo[m_popScoreManager->GetColorChecker()].popPosition.x, popScoreInfo[m_popScoreManager->GetColorChecker()].popPosition.y };
	m_setColor = popScoreInfo[m_popScoreManager->GetColorChecker()].popColor;

	return true;
}

void PopScore::Update()
{
	//フェードアウト時間の計測
	m_fadeTimer += g_gameTime->GetFrameDeltaTime();

	//座標の計算（zは0）
	m_popScoreFontRender.SetPosition(m_fadePosition.x, m_fadePosition.y + m_fadeTimer * MOVE_SPEED, 0.0f);

	//色の計算・設定
	FadingColorCalc();
	m_popScoreFontRender.SetColor(m_fadingColor);

	if (m_fadeTimer >= FADE_DURATION)
	{
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
	m_fadingColor.r = m_setColor.r * (1 - m_fadeTimer / FADE_DURATION);
	m_fadingColor.b = m_setColor.b * (1 - m_fadeTimer / FADE_DURATION);
	m_fadingColor.g = m_setColor.g * (1 - m_fadeTimer / FADE_DURATION);
	m_fadingColor.a = m_setColor.a * (1 - m_fadeTimer / FADE_DURATION);
}
