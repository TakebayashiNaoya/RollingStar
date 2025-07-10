#include "stdafx.h"
#include "Score.h"

#include"Game.h"
#include"Star.h"

bool Score::Start()
{
	m_star = FindGO<Star>("star");
	m_game = FindGO<Game>("game");

	SpriteRenderList();

	SetTextOption(400.0f, 500.0f, 1.5f, g_vec4Yellow, &m_scoreFontRender, L"スコア");

	return true;
}

void Score::Update()
{
	/*チュートリアル～リザルトの間、常にステージとプレイヤーは表示する。
	　インゲーム（スタート～終了）の間だけスコアを表示するためにフラグで管理する。*/
	if (m_game->GetGameEndFlag()) { return; }				//ゲーム終了のフラグ
	if (m_game->GetGameStartFlag() == false) { return; }	//ゲーム開始のフラグ

	TotalScoreCalc();

	SetTextOption(410.0f, 430.0f, 1.5f, g_vec4Yellow, &m_totalScoreFontRender, L"%d", m_totalScore);

	/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
	FontOption text[StarKinds_Num];
	text[enStarKinds_Red] = { m_starCount[enStarKinds_Red],-850.0f,420.0f,1.3f,g_vec4White };
	text[enStarKinds_Orange] = { m_starCount[enStarKinds_Orange],-850.0f,370.0f,1.3f,g_vec4White };
	text[enStarKinds_Purple] = { m_starCount[enStarKinds_Purple],-850.0f,320.0f,1.3f,g_vec4White };
	text[enStarKinds_Blue] = { m_starCount[enStarKinds_Blue],-850.0f,270.0f,1.3f,g_vec4White };
	text[enStarKinds_Green] = { m_starCount[enStarKinds_Green],-850.0f,220.0f,1.3f,g_vec4White };
	text[enStarKinds_Normal] = { m_starCount[enStarKinds_Normal],-850.0f,170.0f,1.3f,g_vec4White };

	for (int i = 0; i < StarKinds_Num; i++) {
		SetTextOption(text[i].pos_x, text[i].pos_y, text[i].scale, text[i].textColor, &m_getStarCountFontRender[i], L"%d", text[i].data);
	}
}

void Score::Render(RenderContext& rc)
{
	if (m_game->GetGameEndFlag() == false) {
		if (m_game->GetGameStartFlag()) {

			m_scoreFontRender.Draw(rc);
			m_totalScoreFontRender.Draw(rc);

			for (int i = 0; i < StarKinds_Num; i++) {
				m_getStarCountFontRender[i].Draw(rc);
			}

			for (int j = 0; j < StarKinds_Num; j++) {
				m_starSpriteRender[j].Draw(rc);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////
// ここからメソッドまとめ。
///////////////////////////////////////////////////////////////////

/// <summary>
/// スプライトレンダーまとめ
/// </summary>
void Score::SpriteRenderList()
{
	m_starSpriteRender[enStarKinds_Red].Init("Assets/sprite/redStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Red].SetPosition({ -900,400,0 });

	m_starSpriteRender[enStarKinds_Orange].Init("Assets/sprite/orangeStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Orange].SetPosition({ -900,350,0 });

	m_starSpriteRender[enStarKinds_Purple].Init("Assets/sprite/purpleStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Purple].SetPosition({ -900,300,0 });

	m_starSpriteRender[enStarKinds_Blue].Init("Assets/sprite/blueStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Blue].SetPosition({ -900,250,0 });

	m_starSpriteRender[enStarKinds_Green].Init("Assets/sprite/greenStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Green].SetPosition({ -900,200,0 });

	m_starSpriteRender[enStarKinds_Normal].Init("Assets/sprite/normalStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Normal].SetPosition({ -900,150,0 });

	for (int i = 0; i < StarKinds_Num; i++) {
		m_starSpriteRender[i].Update();
	}
}

void Score::TotalScoreCalc()
{
	m_totalScore = m_starCount[enStarKinds_Red] * RED_STAR_POINT
		+ m_starCount[enStarKinds_Orange] * ORANGE_STAR_POINT
		+ m_starCount[enStarKinds_Purple] * PURPLE_STAR_POINT
		+ m_starCount[enStarKinds_Blue] * BLUE_STAR_POINT
		+ m_starCount[enStarKinds_Green] * GREEN_STAR_POINT
		+ m_starCount[enStarKinds_Normal] * NORMAL_STAR_POINT;
}

