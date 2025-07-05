#pragma once

class PopScoreManager;

class PopScore :public IGameObject
{
public:
	PopScore();
	~PopScore();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void FadingColorCalc();

	PopScoreManager* m_popScoreManager = nullptr;

	int m_setPoint = 0;
	float m_fadeTimer = 0;
	float m_fadeDuration = 1;
	float m_setScale = 0.0f;

	FontRender m_popScoreFontRender;
	Vector4 m_setColor;
	Vector4 m_fadingColor;
	Vector2 m_setPos;
};

