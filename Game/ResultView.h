#pragma once
class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class Score;
class Star;
class Title;

//�Q�[���N���A�B
class ResultView : public IGameObject
{
public:
	~ResultView();
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���Bg
	void Render(RenderContext& rc);

	//�����o�ϐ��B
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

	SpriteRender m_endSpriteRender;		//�X�v���C�g�����_�\�B
	SpriteRender m_backSpriteRender;	//�X�v���C�g�����_�\�B
	SpriteRender* m_spriteRender;		//�X�v���C�g�����_�\�B

	int m_spriteState = 0;				//�X�v���C�g�X�e�[�g
	float finishCount = 0.0f;
	bool m_isFlag = false;
	int endState = 0;
	int callState = 0;

	//�e�L�X�g�̎��
	//�ǉ�����Ƃ���Text_Num�̏��
	enum FontKinds {
		totalScore,
		redStar,
		orangeStar,
		purpleStar,
		blueStar,
		greenStar,
		normalStar,
		Font_Num
	};

	//�e�L�X�g�I�v�V����
	struct FontOption {
		int data = 0;		//�\������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	FontRender m_fontRender[Font_Num];//�t�H���g�����_�[
};