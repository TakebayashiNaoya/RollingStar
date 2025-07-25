/// <summary>
/// スコアを管理するクラス
/// </summary>
#pragma once
#include "Type.h"

class Game;
class Star;

class Score : public IGameObject
{
public:
	/// <summary>
	/// 合計スコアを取得します。
	/// </summary>
	/// <returns>合計スコア（m_totalScore）の値を返します。</returns>
	int GetTotalScore()
	{
		return m_totalScore;
	}

	/// <summary>
	/// 指定されたインデックスに対応する星の数を取得します。
	/// </summary>
	/// <param name="a">星の数を取得するためのインデックス。</param>
	/// <returns>指定されたインデックスに対応する星の数（int型）。</returns>
	int GetStarCount(int a)
	{
		return m_starCount[a];
	}

	/// <summary>
	/// 指定されたインデックスの星の数を増加させます。
	/// </summary>
	/// <param name="a">星の数を増加させるインデックス。</param>
	void StarCountIncrease(int a)
	{
		m_starCount[a]++;
	}

private:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	/// <summary>
	/// スプライトのレンダーリストを処理します。
	/// </summary>
	void SpriteRenderList();

	/// <summary>
	/// 合計スコアを計算します。
	/// </summary>
	void TotalScoreCalc();

	Game* m_game = nullptr;
	Star* m_star = nullptr;

	SpriteRender m_starSpriteRender[StarKinds_Num];		// スターの画像を描画するための配列。
	SpriteRender m_spriteRender[StarKinds_Num];			// 
	FontRender m_getStarCountFontRender[StarKinds_Num];	// 
	FontRender m_totalScoreFontRender;					// 
	FontRender m_scoreFontRender;						// 

	const struct FontOption
	{
		int data = 0;		//表示したい変数
		float pos_x = 0.0f;	//x座標
		float pos_y = 0.0f;	//y座標
		float scale = 0.0f;	//サイズ
		Vector4 textColor;	//色
	};

	int m_starCount[StarKinds_Num];
	int m_totalScore = 0;
};

