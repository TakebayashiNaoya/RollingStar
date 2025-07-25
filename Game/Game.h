/// <summary>
/// �Q�[���̐i�s���Ǘ�����N���X
/// </summary>
#pragma once
#include"Level3DRender/LevelRender.h"

class BackGround;
class GameCamera;
class GameTimer;
class LoadingView;
class Player;
class PopScoreManager;
class ResultView;
class Score;
class Star;
class StarSpawner;
class Transform;

class Game : public IGameObject
{
private:
	enum EnGameNewGOType
	{
		enGameNewGOType_Init,		// �������珉���������܂��B�P�񂾂��Ăяo�����̂��ŏ��ɌĂԁB
		enGameNewGOType_Step1,		// Player�Ȃǐ��������Ȃ����̂�NewGO���܂��B�����������番�����Ă��������B
		EnGameNewGOType_Step2,		// Star�Ȃ�Level�ő�ʂɔz�u���Ă���I�u�W�F�N�g��NewGO���܂��B�����ŕ����񕪊����s���܂��B
	};

public:
	Game();
	~Game();

	/// <summary>
	/// �Q�[���J�n�t���O�̏�Ԃ��擾���܂��B
	/// </summary>
	/// <returns>�Q�[�����J�n����Ă���ꍇ�� true�A�����łȂ��ꍇ�� false ��Ԃ��܂��B</returns>
	bool GetGameStartFlag()
	{
		return m_isGameStartFlag;
	}

	/// <summary>
	/// �Q�[���J�n�t���O��ݒ肵�܂��B
	/// </summary>
	/// <param name="a">�ݒ肷��Q�[���J�n�t���O�̒l�itrue �܂��� false�j�B</param>
	void SetGameStartFlag(bool a)
	{
		m_isGameStartFlag = a;
	}

	/// <summary>
	/// �Q�[���I���t���O�̏�Ԃ��擾���܂��B
	/// </summary>
	/// <returns>�Q�[�����I�����Ă���ꍇ�� true�A�����łȂ��ꍇ�� false ��Ԃ��܂��B</returns>
	bool GetGameEndFlag()
	{
		return  m_isGameEndFlag;
	}

	/// <summary>
	/// �Q�[���I���t���O��ݒ肵�܂��B
	/// </summary>
	/// <param name="a">�ݒ肷��Q�[���I���t���O�̒l�itrue �܂��� false�j�B</param>
	void SetGameEndFlag(bool a)
	{
		m_isGameEndFlag = a;
	}

private:
	bool Start()override final;
	void Update()override final;

	/// <summary>
	/// ������������܂��B
	/// </summary>
	void InitSky();

	/// <summary>
	/// Init��Update�ɓn���AUpdate�ŗ���𒲐����邱�ƂŃ��[�h��ʂ��������܂��B
	/// </summary>
	void InitLevelObjectDataList();

	/// <summary>
	/// ���x���̃I�u�W�F�N�g�����������܂��B
	/// </summary>
	void InitLevelObject(LevelObjectData& objData);

	BackGround* m_backGround = nullptr;						// �X�e�[�W��`�悷��I�u�W�F�N�g�B
	GameCamera* m_gameCamera = nullptr;						// �J��������������I�u�W�F�N�g�B
	GameTimer* m_gameTimer = nullptr;						// �C���Q�[���̎��Ԃ��Ǘ����A�`�悷��I�u�W�F�N�g�B
	LoadingView* m_loadingView = nullptr;					// ���[�h��ʂ�`�悷��I�u�W�F�N�g�B
	Player* m_player = nullptr;								// �v���C���[���Ǘ�����I�u�W�F�N�g�B
	PopScoreManager* m_popScoreManager = nullptr;			// �X�^�[�擾���Ƀ|�b�v������X�R�A���Ǘ�����I�u�W�F�N�g�B
	ResultView* m_resultView = nullptr;						// ���U���g��ʂ�`�悷��I�u�W�F�N�g�B
	Score* m_score = nullptr;								// �X�R�A���Ǘ�����I�u�W�F�N�g�B
	Transform* m_transform = nullptr;						// �X�e�[�W�ƃX�^�[�̐e�q�t�����Ǘ�����I�u�W�F�N�g�B

	LevelRender m_levelRender;								// LevelRender�̃C���X�^���X�B
	std::vector<StarSpawner*>m_starSpawners;				// StarSpawner�N���X�̃|�C���^�̔z���ێ�����ϐ��i�ϒ��z��j�B
	std::vector<LevelObjectData> m_levelObjectDataList;		// LevelObjectData�N���X�̃C���X�^���X�𕡐��i�[���郊�X�g�B
	int m_objDataListIndex = 0;								// objData��Init�����i�[����ϐ��B

	EnGameNewGOType m_gameNewGOType = enGameNewGOType_Init;	// NewGO����ނ��Ƃɋ�؂�A���[�h��ʂ̏������������ނ��߂Ɏg�p���܂��B

	SkyCube* m_skyCube = nullptr;							// �X�J�C�L���[�u��`�悷��I�u�W�F�N�g�B
	int m_skyCubeType = enSkyCubeType_Night;				// �X�J�C�L���[�u�̎�ނ�ݒ肵�܂��B
	Vector3 m_skyCubePos = Vector3::Zero;					// �X�J�C�L���[�u�̃|�W�V������ݒ肵�܂��i��{�I�Ɍ��_�j�B

	bool m_isGameStartFlag = false;							// �C���Q�[�����X�^�[�g������true�ɂ��āA�e�N���X�̏������n�߂܂��B
	bool m_isGameEndFlag = false;							// �C���Q�[�����I��������true�ɂ��āA�e�N���X�̏������~�߂܂��B
};