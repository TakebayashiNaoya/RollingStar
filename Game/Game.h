///
/// ゲームの進行を管理するクラス
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

//Gameシーンを管理するクラス。
class Game : public IGameObject
{
private:
	enum EnGameNewGOType
	{
		enGameNewGOType_Init,		// 何かしら初期化をします。１回だけ呼び出いものを最初に呼ぶ。
		enGameNewGOType_Step1,		// Playerなど数が多くないものをNewGOします。数が増えたら分割してください。
		EnGameNewGOType_Step2,		// StarなどLevelで大量に配置しているオブジェクトをNewGOします。ここで複数回分割を行います。
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