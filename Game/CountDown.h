/// <summary>
/// ゲームスタート時のカウントダウンクラス
/// </summary>
#pragma once
class Game;

class CountDown :public IGameObject
{
public:
	CountDown();
	~CountDown();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// スプライトレンダーを計算して返します。
	/// </summary>
	/// <returns>計算された SpriteRender オブジェクトへのポインタ。</returns>
	SpriteRender* ComputeSpriteRender();

	Game* m_game = nullptr;					// Game型のポインタ。
	SpriteRender* m_spriteRender = nullptr;	// SpriteRender型のポインタ。

	SpriteRender m_countThreeSpriteRender;		//「3」と表示するためのSpriteRenderインスタンス。
	SpriteRender m_countTwoSpriteRender;		//「2」と表示するためのSpriteRenderインスタンス。
	SpriteRender m_countOneSpriteRender;		//「1」と表示するためのSpriteRenderインスタンス。
	SpriteRender m_countStartSpriteRender;	//「START」と表示するためのSpriteRenderインスタンス。

	float countDown = 0.0f;					// SpriteRenderを切り替える時間を計測するための変数。
};

