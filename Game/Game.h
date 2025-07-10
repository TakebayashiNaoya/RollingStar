///
/// �Q�[���̐i�s���Ǘ�����N���X
///
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

//Game�V�[�����Ǘ�����N���X�B
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
	bool Start()override;
	void Update()override;

private:
	void InitSky();
	void InitBGM();
	void InitLevelObjectDataList();
	void InitLevelObject(LevelObjectData& objData);

public:
	bool GetGameStartFlag()
	{
		return m_isGameStartFlag;
	}
	void SetGameStartFlag(bool a)
	{
		m_isGameStartFlag = a;
	}

	bool GetGameEndFlag()
	{
		return  m_isGameEndFlag;
	}
	void SetGameEndFlag(bool a)
	{
		m_isGameEndFlag = a;
	}

private:
	BackGround* m_backGround = nullptr;
	SoundSource* m_gameBGM = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	LoadingView* m_loadingView = nullptr;
	Player* m_player = nullptr;
	PopScoreManager* m_popScoreManager = nullptr;
	ResultView* m_resultView = nullptr;
	Score* m_score = nullptr;
	Transform* m_transform = nullptr;

private:
	LevelRender m_levelRender;
	std::vector<StarSpawner*>m_starSpawners;
	std::vector<LevelObjectData> m_levelObjectDataList;
	int m_objDataListIndex = 0;
	int m_starSum = 0;

	EnGameNewGOType m_gameNewGOType = enGameNewGOType_Init;

	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Night;
	Vector3 m_skyCubePos = Vector3::Zero;

	bool m_isGameStartFlag = false;
	bool m_isGameEndFlag = false;
};