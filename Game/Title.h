/// <summary>
/// タイトルを管理するクラス
/// </summary>
#pragma once

class Title :public IGameObject
{
private:
	/// <summary>
	/// タイトル削除後、すぐにロード画面を表示させるフレーム処理のために使用する列挙型です。
	/// </summary>
	enum EnTitleStep
	{
		enTitleStep_1,	// ロード画面をNewGOする。
		enTitleStep_2,	// 何もしない（1フレーム待機）。
		enTitleStep_3,	// タイトルを削除する。
	};

public:
	~Title();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	EnTitleStep m_titleStep;				// ロード画面をすぐに表示するために、フレーム処理を行う。
	SpriteRender m_titleViewSpriteRender;	// タイトル画像を描画。
};

