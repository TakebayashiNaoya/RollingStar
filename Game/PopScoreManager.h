///
/// スコアをポップさせるタイミングと色を伝えるクラス
///
#pragma once

class PopScoreManager :public IGameObject
{
public:
	bool Start()override;
	void Update()override;

public:
	void SetPopFlag(bool a)
	{
		isPopFlag = a;
	}
	int GetColorChecker()
	{
		return colorChecker;
	}
	void SetColorChecker(int a)
	{
		colorChecker = a;
	}

private:
	bool isPopFlag = false;
	int colorChecker = 0;
};

