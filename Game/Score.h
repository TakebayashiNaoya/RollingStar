#pragma once
#include "Type.h"

class Star;
class Game;

class Score : public IGameObject
{
public:
	Score();
	~Score();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void SpriteRenderList();
	void TotalScoreCalc();

	//メンバ変数
	Star* m_star = nullptr;
	Game* m_game = nullptr;

	SpriteRender m_starSpriteRender[StarKinds_Num];

	int m_starCount[StarKinds_Num];

	int m_totalScore = 0;		//トータルスコア
	int m_orangeStarCount = 0;	//オレンジスター
	int m_purpleStarCount = 0;	//パープルスター
	int m_blueStarCount = 0;	//ブルースター
	int m_greenStarCount = 0;	//グリーンスター
	int m_normalStarCount = 0;	//ノーマルスター


	//フォントオプション
	struct FontOption {
		int data = 0;		//表示したい変数
		float pos_x = 0.0f;	//x座標
		float pos_y = 0.0f;	//y座標
		float scale = 0.0f;	//サイズ
		Vector4 textColor;	//色
	};


	FontRender m_scoreFontRender;		//「スコア」と表示	
	FontRender m_totalScoreFontRender;	//合計スコアを表示
	FontRender m_getStarCountFontRender[StarKinds_Num];
	SpriteRender m_spriteRender[StarKinds_Num];
};

