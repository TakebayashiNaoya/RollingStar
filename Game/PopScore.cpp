#include "stdafx.h"
#include "PopScore.h"
#include "PopScoreManager.h"
#include "Score.h"
#include "Star.h"
#include "Type.h"

namespace
{
	const float MOVE_SPEED = 150.0f;	// ポップしたスコアの移動速度。
	const float FADE_DURATION = 1.0f;	// フェードの持続時間

	/// <summary>
	/// ポップさせるスコアのオプションを格納する構造体です。
	/// </summary>
	struct PopScoreOptions
	{
		Vector2 popPosition = Vector2::Zero;			// 座標。
		float popScale = 0.0f;							// 大きさ。
		Vector4 popColor = { 0.0f,0.0f,0.0f,0.0f };		// 色。
		int popPoint = 0;								// 得点。
	};

	/// <summary>
	/// ポップスコアオプションの定義済み配列です。各要素はスコアポイントの位置、倍率、色、種類を表します。
	/// </summary>
	const PopScoreOptions POP_SCORE_OPTIONS[] =
	{
		{{ -140.0f,80.0f },2.0f,{ 1.0f,0.0f,0.0f,1.0f },RED_STAR_POINT},		// レッドスター。
		{{ -115.0f,80.0f },1.9f,{ 1.0f,0.5f,0.0f,1.0f },ORANGE_STAR_POINT},		// オレンジスター。
		{{ -110.0f,80.0f },1.8f,{ 1.0f,0.0f,1.0f,1.0f },PURPLE_STAR_POINT},		// パープルスター。
		{{ -105.0f,80.0f },1.7f,{ 0.0f,0.0f,1.0f,1.0f },BLUE_STAR_POINT},		// ブルースター。
		{{ -100.0f,80.0f },1.6f,{ 0.0f,1.0f,0.0f,1.0f },GREEN_STAR_POINT},		// グリーンスター。
		{{ -70.0f,80.0f },1.5f,{ 1.0f,1.0f,0.0f,1.0f },NORMAL_STAR_POINT}		// ノーマルスター。
	};
}

bool PopScore::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");

	SetTextOption(POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popPosition.x,
		POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popPosition.y,
		POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popScale,
		POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popColor,
		&m_popScoreFontRender, L"+%d", POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popPoint);

	m_fadePosition = { POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popPosition.x, POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popPosition.y };
	m_setColor = POP_SCORE_OPTIONS[m_popScoreManager->GetColorChecker()].popColor;

	return true;
}

void PopScore::Update()
{
	m_fadeTimer += g_gameTime->GetFrameDeltaTime();

	m_popScoreFontRender.SetPosition(m_fadePosition.x, m_fadePosition.y + m_fadeTimer * MOVE_SPEED, 0.0f);

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

void PopScore::FadingColorCalc()
{
	const float fadeRatio = 1.0f - (m_fadeTimer / FADE_DURATION);
	m_fadingColor = m_setColor * fadeRatio;
}
