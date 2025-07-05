#pragma once

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

	SpriteRender m_redStarSpriteRender;
	SpriteRender m_orangeStarSpriteRender;
	SpriteRender m_purpleStarSpriteRender;
	SpriteRender m_blueStarSpriteRender;
	SpriteRender m_greenStarSpriteRender;
	SpriteRender m_normalStarSpriteRender;

	int m_totalScore = 0;		//トータルスコア
	int m_redStarCount = 0;		//レッドスター
	int m_orangeStarCount = 0;	//オレンジスター
	int m_purpleStarCount = 0;	//パープルスター
	int m_blueStarCount = 0;	//ブルースター
	int m_greenStarCount = 0;	//グリーンスター
	int m_normalStarCount = 0;	//ノーマルスター


	//テキストの種類
	//追加するときはText_Numの上に
	enum EnFontKinds {
		enFontKinds_Total,
		enFontKinds_Red,
		enFontKinds_Orange,
		enFontKinds_Purple,
		enFontKinds_Blue,
		enFontKinds_Green,
		enFontKinds_Normal,
		Font_Num
	};

	//フォントオプション
	struct FontOption {
		int data = 0;		//表示したい変数
		float pos_x = 0.0f;	//x座標
		float pos_y = 0.0f;	//y座標
		float scale = 0.0f;	//サイズ
		Vector4 textColor;	//色
	};

	//フォントレンダー
	FontRender m_score;
	FontRender m_fontRender[Font_Num];
	SpriteRender m_spriteRender[Font_Num];//スプライトレンダー



};

