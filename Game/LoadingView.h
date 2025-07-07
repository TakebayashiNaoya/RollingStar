#pragma once

class Tutorial;

class LoadingView :public IGameObject
{
public:
	LoadingView();
	~LoadingView();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	//ロードの段階
	enum EnLoadingPhase {
		enLoadingPhase_1,
		enLoadingPhase_2,
		enLoadingPhase_3,
		enLoadingPhase_4,
		enLoadingPhase_5,
		enLoadingPhase_6,
		Phase_Num
	};

	//ロード画面
	SpriteRender m_LoadingSceneSpriteRender;

	//ロード中に表示する星の配列
	SpriteRender m_LoadingPhaseSpriteRenders[Phase_Num];

	//ロードの段階に応じて星を表示
	bool showLoadingPhases[Phase_Num] = { false };

	//Aボタンを押してくださいの字幕
	FontRender m_pushA_FontRender;
};

