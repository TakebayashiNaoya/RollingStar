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

//Game�V�[�����Ǘ�����N���X�B
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//�X�V�����B
	void Update();
	void LevelInit();

	Player* m_player;			//�v���C���[�B
	GameCamera* m_gameCamera;			//�Q�[���J�����B
	BackGround* m_backGround;
	Score* m_score;
	GameTimer* m_gameTimer;
	ResultView* m_resultView;
	Transform* m_transform;
	SoundSource* m_gameBGM;		//�Q�[������BGM�B
	Vector3 m_position;
	//Star* m_starSpawner[25];
	StarSpawner* m_starSpawner[161];
	LevelRender m_levelRender;
	int m_starSum = 0;
	int m_finishTime = 0;
	int m_finishScore = 0;
	bool m_gameEndFlag = false;
	bool m_gameStartFlag = false;
};