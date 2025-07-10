///
/// スコアポップさせる機構を管理するクラス
///
#pragma once

class PopScoreManager;

class PopScore :public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	void FadingColorCalc();

private:
	PopScoreManager* m_popScoreManager = nullptr;

private:
	FontRender m_popScoreFontRender;
	Vector4 m_setColor;
	Vector4 m_fadingColor;
	Vector2 m_setPos = Vector2::Zero;
	int m_setPoint = 0;
	float m_fadeTimer = 0.0f;
	float m_setScale = 0.0f;
};

