#pragma once

class PopScoreManager :public IGameObject
{
public:
	PopScoreManager();
	~PopScoreManager();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc) override;

	bool isPopFlag = false;
	int colorChecker = 0;
};

