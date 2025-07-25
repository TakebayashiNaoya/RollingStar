/// <summary>
/// ロード画面を管理するクラス
/// </summary>
#pragma once

class LoadingView :public IGameObject
{
public:
	/// <summary>
	/// ロードフェーズを表す列挙型です。
	/// </summary>
	enum EnLoadingPhase
	{
		enLoadingPhase_First,	// ロードの進捗1/6を示す。
		enLoadingPhase_Second,	// ロードの進捗2/6を示す。
		enLoadingPhase_Third,	// ロードの進捗3/6を示す。
		enLoadingPhase_Fourth,	// ロードの進捗4/6を示す。
		enLoadingPhase_Fifth,	// ロードの進捗5/6を示す。
		enLoadingPhase_Sixth,	// ロードの進捗6/6を示す。
		Phase_Num
	};

	bool showLoadingPhases[Phase_Num] = { false };	// この配列でロードの進捗を示すスターの初期化と位置設定を行います。

	~LoadingView();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	SpriteRender m_LoadingSceneSpriteRender;				// ロード画面の背景を表示します。
	FontRender m_pushA_FontRender;							// 「PUSH(A)」と表示します。
	SpriteRender m_LoadingPhaseSpriteRenders[Phase_Num];	// ロードの進捗に合わせてスターを表示します。
};

