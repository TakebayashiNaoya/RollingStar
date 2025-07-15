///
/// ゲーム終了画面、リザルト画面、ランキング画面を管理するクラス
///
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
	enum EnViewStates {
		enViewStates_GameEnd,	//ゲーム終了画面を表示
		enViewStates_Result,	//リザルト画面を表示
		enViewStates_Rankings	//ランキングを表示
	};

	//ランキング画面で表示するUI(スプライト)の識別用enum
	enum EnSpritesForRankingView {
		enSpritesForRankingView_Ranking,
		enSpritesForRankingView_GoldCrown,
		enSpritesForRankingView_SilverCrown,
		enSpritesForRankingView_BronzeCrown,
		enSpritesForRankingView_PushA,
		SpritesForRankingView_Num
	};

	enum EnRanking {
		enRanking_1st,
		enRanking_2nd,
		enRanking_3rd,
		Ranking_Num
	};

public:
	~ResultView();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	void RankingUI_InitSetList();
	void SetTotalScoreFontRender();
	void SetGotStarCountFontRender();
	void SetScoreOfRankFontRenderList();

private:
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	SaveData* m_saveData = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

private:
	//常時表示しているm_spriteRenderに入れて切り替える。
	SpriteRender m_endSpriteRender;
	SpriteRender m_resultSpriteRender;
	SpriteRender m_backScreenSpriteRender;
	SpriteRender* m_spriteRender = nullptr;

	EnViewStates m_viewState = enViewStates_GameEnd;
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];
	FontRender m_totalScoreFontRender;
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];
	FontRender m_scoreOfRankFontRenderList[3];

	//スターの獲得数を表示するための構造体
	struct FontOption {
		int data = 0;		//表示する変数
		float pos_x = 0.0f;	//x座標
		float pos_y = 0.0f;	//y座標
		float scale = 0.0f;	//サイズ
		Vector4 textColor;	//色
	};

	float m_timerToResult = 0.0f;

	//Updateの中で一度だけ処理するためのフラグ
	bool onceEndSE = true;
	bool onceCallSE = true;
	bool onceSaveScore = true;
};