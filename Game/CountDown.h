/// <summary>
/// ゲームスタート時のカウントダウンクラス
/// </summary>
#pragma once
class Game;

class CountDown :public IGameObject
{
private:
	/// <summary>
	/// カウントダウンの各段階を表す列挙型です。
	/// </summary>
	enum EnCount
	{
		enCount_Three,	// 「3」。
		enCount_Two,	// 「2」。
		enCount_One,	// 「1」。
		enCount_Start,	// 「START」。
		enCount_Num
	};

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

	Game* m_game = nullptr;							// Game型のポインタ。
	SpriteRender* m_spriteRender = nullptr;			// SpriteRender型のポインタ。

	SpriteRender m_countSpriteRender[enCount_Num];	// enCount_Num 個の SpriteRender オブジェクトを格納する配列です。

	float countDown = 0.0f;							// SpriteRenderを切り替える時間を計測するための変数。
};

