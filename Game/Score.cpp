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
	m_score.SetText(L"スコア");					//テキスト表示
	m_score.SetPosition(400.0f, 500.0f, 0.0f);	//座標
	m_score.SetScale(1.5f);						//サイズ
	m_score.SetColor(g_vec4Yellow);				//色

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

	/// <summary>
	/// テキスト設定。
	/// </summary>
	/// {表示したい変数(intのみ) , x座標 , y座標 , サイズ , 色}
	FontOption text[Font_Num];
	text[enFontKinds_Total] = { m_totalScore,410.0f,430.0f,1.5f,g_vec4Yellow };
	text[enFontKinds_Red] = { m_redStarCount,-850.0f,420.0f,1.3f,g_vec4White };
	text[enFontKinds_Orange] = { m_orangeStarCount,-850.0f,370.0f,1.3f,g_vec4White };
	text[enFontKinds_Purple] = { m_purpleStarCount,-850.0f,320.0f,1.3f,g_vec4White };
	text[enFontKinds_Blue] = { m_blueStarCount,-850.0f,270.0f,1.3f,g_vec4White };
	text[enFontKinds_Green] = { m_greenStarCount,-850.0f,220.0f,1.3f,g_vec4White };
	text[enFontKinds_Normal] = { m_normalStarCount,-850.0f,170.0f,1.3f,g_vec4White };

	for (int i = 0; i < Font_Num; i++)
	{
		wchar_t tmp[256];
		swprintf_s(tmp, 256, L"%d", text[i].data);
		m_fontRender[i].SetText(tmp);										//テキスト表示
		m_fontRender[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0 });	//座標
		m_fontRender[i].SetScale(text[i].scale);							//サイズ
		m_fontRender[i].SetColor(text[i].textColor);						//色
	}
}

void Score::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		if (m_game->m_gameStartFlag == true) {

			m_score.Draw(rc);

			for (int i = 0; i < Font_Num; i++)
			{
				m_fontRender[i].Draw(rc);
			}

			m_redStarSpriteRender.Draw(rc);
			m_orangeStarSpriteRender.Draw(rc);
			m_purpleStarSpriteRender.Draw(rc);
			m_blueStarSpriteRender.Draw(rc);
			m_greenStarSpriteRender.Draw(rc);
			m_normalStarSpriteRender.Draw(rc);

			//m_getStarFontRender.Draw(rc);
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
	m_redStarSpriteRender.Init("Assets/sprite/redStar.dds", 50.0f, 50.0f);
	m_redStarSpriteRender.SetPosition({ -900,400,0 });
	m_redStarSpriteRender.Update();
	m_orangeStarSpriteRender.Init("Assets/sprite/orangeStar.dds", 50.0f, 50.0f);
	m_orangeStarSpriteRender.SetPosition({ -900,350,0 });
	m_orangeStarSpriteRender.Update();
	m_purpleStarSpriteRender.Init("Assets/sprite/purpleStar.dds", 50.0f, 50.0f);
	m_purpleStarSpriteRender.SetPosition({ -900,300,0 });
	m_purpleStarSpriteRender.Update();
	m_blueStarSpriteRender.Init("Assets/sprite/blueStar.dds", 50.0f, 50.0f);
	m_blueStarSpriteRender.SetPosition({ -900,250,0 });
	m_blueStarSpriteRender.Update();
	m_greenStarSpriteRender.Init("Assets/sprite/greenStar.dds", 50.0f, 50.0f);
	m_greenStarSpriteRender.SetPosition({ -900,200,0 });
	m_greenStarSpriteRender.Update();
	m_normalStarSpriteRender.Init("Assets/sprite/normalStar.dds", 50.0f, 50.0f);
	m_normalStarSpriteRender.SetPosition({ -900,150,0 });
	m_normalStarSpriteRender.Update();
}

void Score::TotalScoreCalc()
{
	m_totalScore = m_redStarCount * RED_STAR_POINT
		+ m_orangeStarCount * ORANGE_STAR_POINT
		+ m_purpleStarCount * PURPLE_STAR_POINT
		+ m_blueStarCount * BLUE_STAR_POINT
		+ m_greenStarCount * GREEN_STAR_POINT
		+ m_normalStarCount * NORMAL_STAR_POINT;
}

