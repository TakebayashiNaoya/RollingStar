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

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	//更新処理。
	void Update();
	void LevelInit();
	void InitSky();//空を初期化

	Player* m_player;			//プレイヤー。
	GameCamera* m_gameCamera;			//ゲームカメラ。
	BackGround* m_backGround;
	Score* m_score;
	GameTimer* m_gameTimer;
	ResultView* m_resultView;
	Transform* m_transform;
	SoundSource* m_gameBGM;		//ゲーム中のBGM。
	PopScoreManager* m_popScoreManager;
	Vector3 m_position;
	//Star* m_starSpawner[25];
	StarSpawner* m_starSpawner[161];
	LevelRender m_levelRender;
	int m_starSum = 0;
	int m_finishTime = 0;
	int m_finishScore = 0;
	bool m_gameEndFlag = false;
	bool m_gameStartFlag = false;

	SkyCube* m_skyCube = nullptr;//スカイキューブ
	int m_skyCubeType = enSkyCubeType_Night;
	Vector3 m_skyCubePos = { 0.0f,3000.0f,0.0f };
};