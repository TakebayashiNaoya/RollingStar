/// <summary>
/// スコアポップさせる機構を管理するクラス
/// </summary>
#pragma once

class PopScoreManager;

class PopScore :public IGameObject
{
private:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	/// <summary>
	/// フェード効果のある色の計算を行います。
	/// </summary>
	void FadingColorCalc();

	struct PopScoreInfo
	{
		Vector2 popPosition = Vector2::Zero;
		float popScale = 0.0f;
		Vector4 popColor = { 0.0f,0.0f,0.0f,0.0f };
		int popPoint = 0;
	};


	PopScoreManager* m_popScoreManager = nullptr;

	FontRender m_popScoreFontRender;					// ポップさせるスコアを描画します。
	Vector4 m_setColor = { 0.0f,0.0f,0.0f,0.0f };		// ポップさせるスコアの色を格納します。
	Vector4 m_fadingColor = { 0.0f,0.0f,0.0f,0.0f };	// フェード中の色を格納します。
	Vector2 m_fadePosition = Vector2::Zero;				// ポップさせるスコアの位置を格納します。
	int m_setPoint = 0;									// ポップさせるスコアポイントを格納します。
	float m_fadeTimer = 0.0f;							// フェード効果の継続時間を格納します。
	float m_setScale = 0.0f;							// ポップさせるスコアのサイズを格納します。


};

