///
/// �Q�[���I����ʁA���U���g��ʁA�����L���O��ʂ��Ǘ�����N���X
///
#pragma once
#include "Type.h"

class BackGround;
class Game;
class GameCamera;
class GameTimer;
class Player;
class SaveData;
class Score;
class Star;
class Title;

//�Q�[���N���A�B
class ResultView : public IGameObject
{
private:
	enum EnViewStates {
		enViewStates_GameEnd,	//�Q�[���I����ʂ�\��
		enViewStates_Result,	//���U���g��ʂ�\��
		enViewStates_Rankings	//�����L���O��\��
	};

	//�����L���O��ʂŕ\������UI(�X�v���C�g)�̎��ʗpenum
	enum EnSpritesForRankingView {
		enSpritesForRankingView_Ranking,
		enSpritesForRankingView_GoldCrown,
		enSpritesForRankingView_SilverCrown,
		enSpritesForRankingView_BronzeCrown,
		enSpritesForRankingView_PushA,
		SpritesForRankingView_Num
	};

	enum EnRanking {
		enRanking_1st,
		enRanking_2nd,
		enRanking_3rd,
		Ranking_Num
	};

public:
	~ResultView();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:
	void RankingUI_InitSetList();
	void SetTotalScoreFontRender();
	void SetGotStarCountFontRender();
	void SetScoreOfRankFontRenderList();

private:
	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	SaveData* m_saveData = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

private:
	//�펞�\�����Ă���m_spriteRender�ɓ���Đ؂�ւ���B
	SpriteRender m_endSpriteRender;
	SpriteRender m_resultSpriteRender;
	SpriteRender m_backScreenSpriteRender;
	SpriteRender* m_spriteRender = nullptr;

	EnViewStates m_viewState = enViewStates_GameEnd;
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];
	FontRender m_totalScoreFontRender;
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];
	FontRender m_scoreOfRankFontRenderList[3];

	//�X�^�[�̊l������\�����邽�߂̍\����
	struct FontOption {
		int data = 0;		//�\������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	float m_timerToResult = 0.0f;

	//Update�̒��ň�x�����������邽�߂̃t���O
	bool onceEndSE = true;
	bool onceCallSE = true;
	bool onceSaveScore = true;
};