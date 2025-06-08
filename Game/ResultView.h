#pragma once
class GameTimer;
//ゲームクリア。
class ResultView : public IGameObject
{
public:
	ResultView();
	~ResultView();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);

	//メンバ変数。
	GameTimer* m_gameTimer;

	SpriteRender m_endSpriteRender; //スプライトレンダ―。
	SpriteRender m_backSpriteRender; //スプライトレンダ―。
	SpriteRender* m_spriteRender; //スプライトレンダ―。
	FontRender m_fontRender;//フォントレンダー
	int m_spriteState = 0;//スプライトステート
	float finishCount = 0.0f;
	bool m_isFlag = false;
};