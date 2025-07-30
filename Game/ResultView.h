/// <summary>
/// ゲーム終了画面、リザルト画面、ランキング画面を管理するクラス
/// </summary>
#pragma once
#include "Type.h"

class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class SaveData;
class Score;
class Star;
class Title;

//ゲームクリア。
class ResultView : public IGameObject
{
private:
	/// <summary>
	/// ゲームの表示状態を表す列挙型です。
	/// </summary>
	enum EnViewStates
	{
		enViewStates_GameEnd,	//ゲーム終了画面を表示
		enViewStates_Result,	//リザルト画面を表示
		enViewStates_Rankings,	//ランキングを表示
		enViewStates_Num
	};

	/// <summary>
	/// ランキングビューで使用されるスプライトを表す列挙型です。
	/// </summary>
	enum EnSpritesForRankingView
	{
		enSpritesForRankingView_Ranking,		// 「ランキング」文字列の画像。
		enSpritesForRankingView_GoldCrown,		// 金冠のイラスト。
		enSpritesForRankingView_SilverCrown,	// 銀冠のイラスト。
		enSpritesForRankingView_BronzeCrown,	// 銅冠のイラスト。
		enSpritesForRankingView_PushA,			// 「Push(A)」文字列の画像。
		enSpritesForRankingView_Num
	};

	/// <summary>
	/// ランキングの順位を表す列挙型です。
	/// </summary>
	enum EnRanking
	{
		enRanking_First,	// 1位。
		enRanking_Second,	// 2位。
		enRanking_Third,	// 3位。
		enRanking_Num
	};

public:
	~ResultView();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// ランキングUIのリストを初期化して設定します。
	/// </summary>
	void SetupRankingUI();

	/// <summary>
	/// 合計スコアのフォントを設定します。
	/// </summary>
	void SetupTotalScoreFontRender();

	/// <summary>
	/// スター獲得数のフォントを設定します。
	/// </summary>
	void SetupGotStarCountFontRender();

	/// <summary>
	/// セーブデータの上3つのスコアのフォントを設定して表示します。
	/// </summary>
	void SetupScoreOfRankFontRenderList();

	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	SaveData* m_saveData = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

	SpriteRender* m_spriteRender = nullptr;								// m_spriteRendersを代入して常時表示します。
	SpriteRender m_spriteRenders[enViewStates_Num];						// 「FINISH」→リザルト→ランキングのスプライトを格納します。

	EnViewStates m_viewState = enViewStates_GameEnd;					// 終了→リザルト→ランキングのステートを格納します。
	SpriteRender m_spritesForRankingView[enSpritesForRankingView_Num];	// ランキング画面で表示するUIを配列で格納します。
	FontRender m_totalScoreFontRender;									// 合計スコアを表示します。
	FontRender m_gotStarCountFontRenderList[enStarKinds_Num];				// 各スターの取得数を配列で格納し表示します。
	FontRender m_scoreOfRankFontRenderList[enRanking_Num];				// ランキング（1位、2位、3位）のスコアを配列で格納し表示します。

	float m_timerToResult = 0.0f;	// FINISHからリザルトに切り替わるまでの時間を格納します。

	/// <summary>
	/// Updateの中で一度だけ処理するためのフラグ。
	/// </summary>
	bool onceEndSE = true;		// FINISH画面で一度だけSEを再生するためのフラグ。
	bool onceCallSE = true;		// リザルト画面で歓声SEを一度だけ再生するためのフラグ。
	bool onceSaveScore = true;	// 一度だけスコアをセーブするためのフラグ。
};