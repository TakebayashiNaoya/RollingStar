#pragma once
#include "Type.h"

class Game;
class Star;

class Score : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

public:
	int GetTotalScore()
	{
		return m_totalScore;
	}
	int GetStarCount(int a)
	{
		return m_starCount[a];
	}
	void StarCountIncrease(int a)
	{
		m_starCount[a]++;
	}

private:
	void SpriteRenderList();
	void TotalScoreCalc();

private:
	Game* m_game = nullptr;
	Star* m_star = nullptr;

private:
	SpriteRender m_starSpriteRender[StarKinds_Num];
	SpriteRender m_spriteRender[StarKinds_Num];
	FontRender m_getStarCountFontRender[StarKinds_Num];
	FontRender m_totalScoreFontRender;
	FontRender m_scoreFontRender;

	const struct FontOption {
		int data = 0;		//�\���������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	int m_starCount[StarKinds_Num];
	int m_totalScore = 0;
};

