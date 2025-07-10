///
/// ロード画面を管理するクラス
///
#pragma once

class Tutorial;

class LoadingView :public IGameObject
{
public:
	enum EnLoadingPhase {
		enLoadingPhase_1,
		enLoadingPhase_2,
		enLoadingPhase_3,
		enLoadingPhase_4,
		enLoadingPhase_5,
		enLoadingPhase_6,
		Phase_Num
	};
	bool showLoadingPhases[Phase_Num] = { false };

public:
	LoadingView();
	~LoadingView();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	SpriteRender m_LoadingSceneSpriteRender;
	FontRender m_pushA_FontRender;
	SpriteRender m_LoadingPhaseSpriteRenders[Phase_Num];
};

