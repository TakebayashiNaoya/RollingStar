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
		enViewStates_Rankings	//ランキングを表示
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
		SpritesForRankingView_Num
	};

	/// <summary>
	/// ランキングの順位を表す列挙型です。
	/// </summary>
	enum EnRanking
	{
		enRanking_1st,	// 1位。
		enRanking_2nd,	// 2位。
		enRanking_3rd,	// 3位。
		Ranking_Num
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
	void RankingUI_InitSetList();

	/// <summary>
	/// 合計スコアのフォントレンダリングを設定します。
	/// </summary>
	void SetTotalScoreFontRender();

	/// <summary>
	/// スター獲得数のフォントレンダリングを設定します。
	/// </summary>
	void SetGotStarCountFontRender();

	/// <summary>
	/// ランクフォントレンダーリストのスコアを設定します。
	/// </summary>
	void SetScoreOfRankFontRenderList();

	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	SaveData* m_saveData = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

	/// <summary>
	/// 常時表示しているm_spriteRenderに入れて切り替えます。
	/// </summary>
	SpriteRender m_endSpriteRender;			//「FINISH」の画像を表示。
	SpriteRender m_resultSpriteRender;		// リザルト画面を表紙。
	SpriteRender m_backScreenSpriteRender;	// ランキング画面で半透明の黒背景を表示。
	SpriteRender* m_spriteRender = nullptr;

	EnViewStates m_viewState = enViewStates_GameEnd;					// 終了→リザルト→ランキングのステートを格納します。
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];	// ランキング画面で表示するUIを配列で格納します。
	FontRender m_totalScoreFontRender;									// 合計スコアを表示します。
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];				// 各スターの取得数を配列で格納し表示します。
	FontRender m_scoreOfRankFontRenderList[3];							// ランキング（1位、2位、3位）のスコアを配列で格納し表示します。

	/// <summary>
	/// スターの獲得数を表示するための構造体。
	/// </summary>
	struct FontOption
	{
		int data = 0;		// 表示する変数。
		float pos_x = 0.0f;	// x座標。
		float pos_y = 0.0f;	// y座標。
		float scale = 0.0f;	// サイズ。
		Vector4 textColor;	// 色。
	};

	float m_timerToResult = 0.0f;	// FINISHからリザルトに切り替わるまでの時間を格納します。

	/// <summary>
	/// Updateの中で一度だけ処理するためのフラグ。
	/// </summary>
	bool onceEndSE = true;		// FINISH画面で一度だけSEを再生するためのフラグ。
	bool onceCallSE = true;		// リザルト画面で歓声SEを一度だけ再生するためのフラグ。
	bool onceSaveScore = true;	// 一度だけスコアをセーブするためのフラグ。
};