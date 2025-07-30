/// <summary>
/// チュートリアルを管理するクラス
/// </summary>
#pragma once

class Tutorial :public IGameObject
{
public:
	~Tutorial();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	SpriteRender m_tutorialSpriteRender;	// チュートリアル画面を表示する。
};

