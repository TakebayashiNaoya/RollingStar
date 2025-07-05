#pragma once

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

	SpriteRender m_redStarSpriteRender;
	SpriteRender m_orangeStarSpriteRender;
	SpriteRender m_purpleStarSpriteRender;
	SpriteRender m_blueStarSpriteRender;
	SpriteRender m_greenStarSpriteRender;
	SpriteRender m_normalStarSpriteRender;

	int m_totalScore = 0;		//�g�[�^���X�R�A
	int m_redStarCount = 0;		//���b�h�X�^�[
	int m_orangeStarCount = 0;	//�I�����W�X�^�[
	int m_purpleStarCount = 0;	//�p�[�v���X�^�[
	int m_blueStarCount = 0;	//�u���[�X�^�[
	int m_greenStarCount = 0;	//�O���[���X�^�[
	int m_normalStarCount = 0;	//�m�[�}���X�^�[


	//�e�L�X�g�̎��
	//�ǉ�����Ƃ���Text_Num�̏��
	enum EnFontKinds {
		enFontKinds_Total,
		enFontKinds_Red,
		enFontKinds_Orange,
		enFontKinds_Purple,
		enFontKinds_Blue,
		enFontKinds_Green,
		enFontKinds_Normal,
		Font_Num
	};

	//�t�H���g�I�v�V����
	struct FontOption {
		int data = 0;		//�\���������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	//�t�H���g�����_�[
	FontRender m_score;
	FontRender m_fontRender[Font_Num];
	SpriteRender m_spriteRender[Font_Num];//�X�v���C�g�����_�[



};

