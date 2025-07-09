#pragma once
#include "Type.h"

class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class Score;
class Star;
class Title;
class SaveData;

//�Q�[���N���A�B
class ResultView : public IGameObject
{
public:
	~ResultView();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void RankingUI_InitSetList();
	void SetScoreFontRender();
	void SetTotalScoreFontRender();
	void SetGotStarCountFontRender();
	void SetScoreOfRankFontRenderList();

	void EndSE();
	void CallSE();
	void TriggerSE();

	//�����o�ϐ��B
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;
	SaveData* m_saveData = nullptr;

	//�ʂ�����������肪�ʓ|�������̂ŁA�펞�\�����Ă���m_spriteRender�ɓ���Đ؂�ւ���B
	SpriteRender m_endSpriteRender;
	SpriteRender m_resultSpriteRender;
	SpriteRender m_backScreenSpriteRender;
	SpriteRender* m_spriteRender;




	float m_timerToResult = 0.0f;
	bool m_isFlag = false;
	int endState = 0;
	int callState = 0;
	int saveState = 0;

	//��ʂ̐؂�ւ����X�e�[�g�Ǘ�
	int m_viewState = enViewStates_GameEnd;
	enum EnViewStates {
		enViewStates_GameEnd,	//�Q�[���I����ʂ�\��
		enViewStates_Result,	//���U���g��ʂ�\��
		enViewStates_Rankings	//�����L���O��\��
	};

	//�����L���O��ʂŕ\������UI(�X�v���C�g)��Render�z��Ǝ��ʗpenum
	enum EnSpritesForRankingView {
		enSpritesForRankingView_Ranking,
		enSpritesForRankingView_GoldCrown,
		enSpritesForRankingView_SilverCrown,
		enSpritesForRankingView_BronzeCrown,
		enSpritesForRankingView_PushA,
		SpritesForRankingView_Num
	};
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];

	FontRender m_totalScoreFontRender;	//���v�X�R�A��\��
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];

	//�X�^�[�̊l������\�����邽�߂̍\����
	struct FontOption {
		int data = 0;		//�\������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	//���3�̃����L���O
	enum EnRanking {
		enRanking_1st,
		enRanking_2nd,
		enRanking_3rd,
		Ranking_Num
	};
	FontRender m_scoreOfRankFontRenderList[3];
};