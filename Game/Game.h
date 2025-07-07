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

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
private:
	enum EnGameNewGOType
	{
		enGameNewGOType_Init,		// 何かしら初期化をします。１回だけ呼び出いものを最初に呼ぶ。
		enGameNewGOType_Step1,		// Playerなど数が多くないものをNewGOします。数が増えたら分割してください
		EnGameNewGOType_Step2,		// StarなどLevelで大量に配置しているオブジェクトをNewGOします。ここで複数回分割を行います
	};

public:
	Game();
	~Game();
	bool Start();
	void Update();
	void InitSky();//空を初期化
	void InitLevelObjectDataList();
	void InitLevelObject(LevelObjectData& objData);

	Player* m_player;			//プレイヤー。
	GameCamera* m_gameCamera;			//ゲームカメラ。
	BackGround* m_backGround;
	Score* m_score;
	GameTimer* m_gameTimer;
	ResultView* m_resultView;
	Transform* m_transform = nullptr;
	SoundSource* m_gameBGM;		//ゲーム中のBGM。
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

	//スカイキューブ
	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Night;
	Vector3 m_skyCubePos = { 0.0f,3000.0f,0.0f };

};