#pragma once
class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class Score;
class Star;
class Title;

//ゲームクリア。
class ResultView : public IGameObject
{
public:
	ResultView();
	~ResultView();
	bool Start();
	//更新処理。
	void Update();
	//描画処理。g
	void Render(RenderContext& rc);

	//メンバ変数。
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

	SpriteRender m_endSpriteRender; //スプライトレンダ―。
	SpriteRender m_backSpriteRender; //スプライトレンダ―。
	SpriteRender* m_spriteRender; //スプライトレンダ―。
	FontRender m_fontRender;//フォントレンダー
	int m_spriteState = 0;//スプライトステート
	float finishCount = 0.0f;
	bool m_isFlag = false;
	int endState = 0;
	int callState = 0;
};