#include "stdafx.h"
#include "Score.h"
#include"Star.h"
#include"Game.h"
#include"Type.h"

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

	SpriteRenderList();

	//「スコア」表示
	m_scoreFontRender.SetText(L"スコア");					//テキスト表示
	m_scoreFontRender.SetPosition(400.0f, 500.0f, 0.0f);	//座標
	m_scoreFontRender.SetScale(1.5f);						//サイズ
	m_scoreFontRender.SetColor(g_vec4Yellow);				//色

	return true;
}

void Score::Update()
{
	/*チュートリアル～リザルトの間、常にステージとプレイヤーは表示する。
	　インゲーム（スタート～終了）の間だけスコアを表示するためにフラグで管理する。*/
	if (m_game->m_gameEndFlag == true) { return; }		//ゲーム終了のフラグ
	if (m_game->m_gameStartFlag == false) { return; }	//ゲーム開始のフラグ

	//合計スコア計算
	TotalScoreCalc();

	//合計スコア表示
	wchar_t tmp[256];
	swprintf_s(tmp, 256, L"%d", m_totalScore);
	m_totalScoreFontRender.SetText(tmp);
	m_totalScoreFontRender.SetPosition({ 410.0f,430.0f ,0.0f });
	m_totalScoreFontRender.SetScale(1.5f);
	m_totalScoreFontRender.SetColor(g_vec4Yellow);

	/// <summary>
	/// テキスト設定。
	/// </summary>
	/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
	FontOption text[StarKinds_Num];
	text[enStarKinds_Red] = { m_starCount[enStarKinds_Red],-850.0f,420.0f,1.3f,g_vec4White };
	text[enStarKinds_Orange] = { m_starCount[enStarKinds_Orange],-850.0f,370.0f,1.3f,g_vec4White };
	text[enStarKinds_Purple] = { m_starCount[enStarKinds_Purple],-850.0f,320.0f,1.3f,g_vec4White };
	text[enStarKinds_Blue] = { m_starCount[enStarKinds_Blue],-850.0f,270.0f,1.3f,g_vec4White };
	text[enStarKinds_Green] = { m_starCount[enStarKinds_Green],-850.0f,220.0f,1.3f,g_vec4White };
	text[enStarKinds_Normal] = { m_starCount[enStarKinds_Normal],-850.0f,170.0f,1.3f,g_vec4White };

	for (int i = 0; i < StarKinds_Num; i++)
	{
		wchar_t tmp[256];
		swprintf_s(tmp, 256, L"%d", text[i].data);
		m_getStarCountFontRender[i].SetText(tmp);										//テキスト表示
		m_getStarCountFontRender[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0 });	//座標
		m_getStarCountFontRender[i].SetScale(text[i].scale);							//サイズ
		m_getStarCountFontRender[i].SetColor(text[i].textColor);						//色
	}
}

void Score::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		if (m_game->m_gameStartFlag == true) {

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

