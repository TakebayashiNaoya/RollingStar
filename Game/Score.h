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
	int GetTotalScore()const
	{
		return m_totalScore;
	}

	/// <summary>
	/// 指定されたインデックスに対応する星の数を取得します。
	/// </summary>
	/// <param name="a">星の数を取得するためのインデックス。</param>
	/// <returns>指定されたインデックスに対応する星の数（int型）。</returns>
	int GetStarCount(int a)const
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

	SpriteRender m_starSpriteRender[enStarKinds_Num];		// スターの画像を描画するための配列。
	FontRender m_getStarCountFontRender[enStarKinds_Num];	// 獲得したスターの数を表示するフォントレンダー。
	FontRender m_totalScoreFontRender;						// 合計スコアを表示するフォントレンダー。
	FontRender m_scoreFontRender;							// 「スコア」と表示するフォントレンダー。

	int m_starCount[enStarKinds_Num];						// 各スターの獲得数を格納する配列。
	int m_totalScore = 0;									// 合計スコアを格納する変数。
};

