#pragma once
#include "sound/SoundSource.h"
#include"Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class BackGround;
class Transform;
class Star;
class Score;
class GameTimer;
class ResultView;
class StarSpawner;
class PopScoreManager;
class LoadingView;

//Game�V�[�����Ǘ�����N���X�B
class Game : public IGameObject
{
private:
	enum EnGameNewGOType
	{
		enGameNewGOType_Init,		// �������珉���������܂��B�P�񂾂��Ăяo�����̂��ŏ��ɌĂԁB
		enGameNewGOType_Step1,		// Player�Ȃǐ��������Ȃ����̂�NewGO���܂��B�����������番�����Ă�������
		EnGameNewGOType_Step2,		// Star�Ȃ�Level�ő�ʂɔz�u���Ă���I�u�W�F�N�g��NewGO���܂��B�����ŕ����񕪊����s���܂�
	};

public:
	Game();
	~Game();
	bool Start();
	void Update();
	void InitSky();//���������
	void InitLevelObjectDataList();
	void InitLevelObject(LevelObjectData& objData);

	Player* m_player;			//�v���C���[�B
	GameCamera* m_gameCamera;			//�Q�[���J�����B
	BackGround* m_backGround;
	Score* m_score;
	GameTimer* m_gameTimer;
	ResultView* m_resultView;
	Transform* m_transform = nullptr;
	SoundSource* m_gameBGM;		//�Q�[������BGM�B
	PopScoreManager* m_popScoreManager;
	LoadingView* m_loadingView=nullptr;

	Vector3 m_position;
	//Star* m_starSpawner[25];
	//StarSpawner* m_starSpawner[161];
	std::vector<StarSpawner*>m_starSpawners;
	std::vector<LevelObjectData> m_levelObjectDataList;
	int m_objDataListIndex = 0;
	LevelRender m_levelRender;
	EnGameNewGOType m_gameNewGOType = enGameNewGOType_Init;
	int m_starSum = 0;
	int m_finishTime = 0;
	int m_finishScore = 0;
	bool m_gameEndFlag = false;
	bool m_gameStartFlag = false;

	//�X�J�C�L���[�u
	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Night;
	Vector3 m_skyCubePos = { 0.0f,3000.0f,0.0f };

};