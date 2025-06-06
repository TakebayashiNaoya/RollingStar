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

	Player* m_player;			//プレイヤー。
	GameCamera* m_gameCamera;			//ゲームカメラ。
	BackGround* m_backGround;
	Score* m_score;
	GameTimer* m_gameTimer;
	Transform* m_transform;
	SoundSource* m_gameBGM;		//ゲーム中のBGM。
	Vector3 m_position;
	Star* m_star[25];
	LevelRender m_levelRender;
	int starSum = 0;
};