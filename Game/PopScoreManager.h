/// <summary>
/// スコアをポップさせるタイミングと色を伝えるクラス
/// </summary>
#pragma once

class PopScoreManager :public IGameObject
{
public:
	/// <summary>
	/// 他のクラスでtrueにして、スコアをポップさせる合図を出します。
	/// </summary>
	/// <param name="a">設定するフラグの値（true または false）。</param>
	const void SetPopFlag(bool a)
	{
		isPopFlag = a;
	}

	/// <summary>
	/// Starクラスから、消滅したスターの色を取得します。
	/// </summary>
	/// <returns>colorChecker の現在の値を返します。</returns>
	const int GetColorChecker()
	{
		return colorChecker;
	}

	/// <summary>
	/// スタークラスから消滅したスターの色を受け取ります。
	/// </summary>
	/// <param name="a">設定する colorChecker の値。</param>
	const void SetColorChecker(int a)
	{
		colorChecker = a;
	}

private:
	void Update()override final;

	bool isPopFlag = false;	// スコアをポップさせるフラグを格納します。
	int colorChecker = 0;	// 消滅したスターの色を格納し、PopScoreクラスに渡します。
};

