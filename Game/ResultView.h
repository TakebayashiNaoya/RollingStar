#pragma once
#include "Type.h"

class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class Score;
class Star;
class Title;
class SaveData;

//ゲームクリア。
class ResultView : public IGameObject
{
public:
	~ResultView();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void RankingUI_InitSetList();
	void SetScoreFontRender();
	void SetTotalScoreFontRender();
	void SetGotStarCountFontRender();
	void SetScoreOfRankFontRenderList();

	void EndSE();
	void CallSE();
	void TriggerSE();

	//メンバ変数。
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;
	SaveData* m_saveData = nullptr;

	//写したり消したりが面倒くさいので、常時表示しているm_spriteRenderに入れて切り替える。
	SpriteRender m_endSpriteRender;
	SpriteRender m_resultSpriteRender;
	SpriteRender m_backScreenSpriteRender;
	SpriteRender* m_spriteRender;




	float m_timerToResult = 0.0f;
	bool m_isFlag = false;
	int endState = 0;
	int callState = 0;
	int saveState = 0;

	//画面の切り替えをステート管理
	int m_viewState = enViewStates_GameEnd;
	enum EnViewStates {
		enViewStates_GameEnd,	//ゲーム終了画面を表示
		enViewStates_Result,	//リザルト画面を表示
		enViewStates_Rankings	//ランキングを表示
	};

	//ランキング画面で表示するUI(スプライト)のRender配列と識別用enum
	enum EnSpritesForRankingView {
		enSpritesForRankingView_Ranking,
		enSpritesForRankingView_GoldCrown,
		enSpritesForRankingView_SilverCrown,
		enSpritesForRankingView_BronzeCrown,
		enSpritesForRankingView_PushA,
		SpritesForRankingView_Num
	};
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];

	FontRender m_totalScoreFontRender;	//合計スコアを表示
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];

	//スターの獲得数を表示するための構造体
	struct FontOption {
		int data = 0;		//表示する変数
		float pos_x = 0.0f;	//x座標
		float pos_y = 0.0f;	//y座標
		float scale = 0.0f;	//サイズ
		Vector4 textColor;	//色
	};

	//上位3つのランキング
	enum EnRanking {
		enRanking_1st,
		enRanking_2nd,
		enRanking_3rd,
		Ranking_Num
	};
	FontRender m_scoreOfRankFontRenderList[3];
};