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
	ResultView();
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

	SpriteRender m_endSpriteRender; //�X�v���C�g�����_�\�B
	SpriteRender m_backSpriteRender; //�X�v���C�g�����_�\�B
	SpriteRender* m_spriteRender; //�X�v���C�g�����_�\�B
	FontRender m_fontRender;//�t�H���g�����_�[
	int m_spriteState = 0;//�X�v���C�g�X�e�[�g
	float finishCount = 0.0f;
	bool m_isFlag = false;
	int endState = 0;
	int callState = 0;
};