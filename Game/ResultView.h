/// <summary>
/// �Q�[���I����ʁA���U���g��ʁA�����L���O��ʂ��Ǘ�����N���X
/// </summary>
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
	/// <summary>
	/// �Q�[���̕\����Ԃ�\���񋓌^�ł��B
	/// </summary>
	enum EnViewStates
	{
		enViewStates_GameEnd,	//�Q�[���I����ʂ�\��
		enViewStates_Result,	//���U���g��ʂ�\��
		enViewStates_Rankings	//�����L���O��\��
	};

	/// <summary>
	/// �����L���O�r���[�Ŏg�p�����X�v���C�g��\���񋓌^�ł��B
	/// </summary>
	enum EnSpritesForRankingView
	{
		enSpritesForRankingView_Ranking,		// �u�����L���O�v������̉摜�B
		enSpritesForRankingView_GoldCrown,		// �����̃C���X�g�B
		enSpritesForRankingView_SilverCrown,	// �⊥�̃C���X�g�B
		enSpritesForRankingView_BronzeCrown,	// �����̃C���X�g�B
		enSpritesForRankingView_PushA,			// �uPush(A)�v������̉摜�B
		SpritesForRankingView_Num
	};

	/// <summary>
	/// �����L���O�̏��ʂ�\���񋓌^�ł��B
	/// </summary>
	enum EnRanking
	{
		enRanking_1st,	// 1�ʁB
		enRanking_2nd,	// 2�ʁB
		enRanking_3rd,	// 3�ʁB
		Ranking_Num
	};

public:
	~ResultView();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// �����L���OUI�̃��X�g�����������Đݒ肵�܂��B
	/// </summary>
	void RankingUI_InitSetList();

	/// <summary>
	/// ���v�X�R�A�̃t�H���g�����_�����O��ݒ肵�܂��B
	/// </summary>
	void SetTotalScoreFontRender();

	/// <summary>
	/// �X�^�[�l�����̃t�H���g�����_�����O��ݒ肵�܂��B
	/// </summary>
	void SetGotStarCountFontRender();

	/// <summary>
	/// �����N�t�H���g�����_�[���X�g�̃X�R�A��ݒ肵�܂��B
	/// </summary>
	void SetScoreOfRankFontRenderList();

	BackGround* m_backGround = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	Player* m_player = nullptr;
	SaveData* m_saveData = nullptr;
	Score* m_score = nullptr;
	Star* m_star = nullptr;
	Title* m_title = nullptr;

	/// <summary>
	/// �펞�\�����Ă���m_spriteRender�ɓ���Đ؂�ւ��܂��B
	/// </summary>
	SpriteRender m_endSpriteRender;			//�uFINISH�v�̉摜��\���B
	SpriteRender m_resultSpriteRender;		// ���U���g��ʂ�\���B
	SpriteRender m_backScreenSpriteRender;	// �����L���O��ʂŔ������̍��w�i��\���B
	SpriteRender* m_spriteRender = nullptr;

	EnViewStates m_viewState = enViewStates_GameEnd;					// �I�������U���g�������L���O�̃X�e�[�g���i�[���܂��B
	SpriteRender m_spritesForRankingView[SpritesForRankingView_Num];	// �����L���O��ʂŕ\������UI��z��Ŋi�[���܂��B
	FontRender m_totalScoreFontRender;									// ���v�X�R�A��\�����܂��B
	FontRender m_gotStarCountFontRenderList[StarKinds_Num];				// �e�X�^�[�̎擾����z��Ŋi�[���\�����܂��B
	FontRender m_scoreOfRankFontRenderList[3];							// �����L���O�i1�ʁA2�ʁA3�ʁj�̃X�R�A��z��Ŋi�[���\�����܂��B

	/// <summary>
	/// �X�^�[�̊l������\�����邽�߂̍\���́B
	/// </summary>
	struct FontOption
	{
		int data = 0;		// �\������ϐ��B
		float pos_x = 0.0f;	// x���W�B
		float pos_y = 0.0f;	// y���W�B
		float scale = 0.0f;	// �T�C�Y�B
		Vector4 textColor;	// �F�B
	};

	float m_timerToResult = 0.0f;	// FINISH���烊�U���g�ɐ؂�ւ��܂ł̎��Ԃ��i�[���܂��B

	/// <summary>
	/// Update�̒��ň�x�����������邽�߂̃t���O�B
	/// </summary>
	bool onceEndSE = true;		// FINISH��ʂň�x����SE���Đ����邽�߂̃t���O�B
	bool onceCallSE = true;		// ���U���g��ʂŊ���SE����x�����Đ����邽�߂̃t���O�B
	bool onceSaveScore = true;	// ��x�����X�R�A���Z�[�u���邽�߂̃t���O�B
};