#pragma once
#include "Type.h"

class Star;
class Game;

class Score : public IGameObject
{
public:
	Score();
	~Score();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void SpriteRenderList();
	void TotalScoreCalc();

	//�����o�ϐ�
	Star* m_star = nullptr;
	Game* m_game = nullptr;

	SpriteRender m_starSpriteRender[StarKinds_Num];

	int m_starCount[StarKinds_Num];

	int m_totalScore = 0;		//�g�[�^���X�R�A
	int m_orangeStarCount = 0;	//�I�����W�X�^�[
	int m_purpleStarCount = 0;	//�p�[�v���X�^�[
	int m_blueStarCount = 0;	//�u���[�X�^�[
	int m_greenStarCount = 0;	//�O���[���X�^�[
	int m_normalStarCount = 0;	//�m�[�}���X�^�[


	//�t�H���g�I�v�V����
	struct FontOption {
		int data = 0;		//�\���������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};


	FontRender m_scoreFontRender;		//�u�X�R�A�v�ƕ\��	
	FontRender m_totalScoreFontRender;	//���v�X�R�A��\��
	FontRender m_getStarCountFontRender[StarKinds_Num];
	SpriteRender m_spriteRender[StarKinds_Num];
};

