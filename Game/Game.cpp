#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "sound/SoundEngine.h"
//#include"GameClear.h"
#include"Star.h"
#include"Transform.h"
#include"Score.h"
#include"GameTimer.h"

Game::Game()
{
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");



	//背景のオブジェクトを作る。
	//m_backGround = NewGO<BackGround>(0, "background");

	//m_star = NewGO<Star>(0, "star");
	//m_star->

		//transform = NewGO<Transform>(0);

		////Starクラスのオブジェクトを作る。
		//Star* star1 = NewGO<Star>(0, "star");
		//star1->position = { 100.0f,150.0f,-200.0f };
		//star1->firstPosition = star1->position;

		//Star* star2 = NewGO<Star>(0, "star");
		//star2->position = { 1000.0f,150.0f,-200.0f };
		//star2->firstPosition = star2->position;

		//Star* star3 = NewGO<Star>(0, "star");
		//star3->position = { 100.0f,250.0f,400.0f };
		//star3->firstPosition = star3->position;

		//Star* star4 = NewGO<Star>(0, "star");
		//star4->position = { 2300.0f,50.0f,-200.0f };
		//star4->firstPosition = star4->position;

		//Star* star5 = NewGO<Star>(0, "star");
		//star5->position = { 2700.0f,450.0f,400.0f };
		//star5->firstPosition = star5->position;

		////ゲーム中のBGMを読み込む。
		//g_soundEngine->ResistWaveFileBank(1, "Assets/sound/gamebgm.wav");
		////ゲーム中のBGMを再生する。
		//gameBGM = NewGO<SoundSource>(0);
		//gameBGM->Init(1);
		//gameBGM->Play(true);


}

Game::~Game()
{
	//ださい
	//for (int starCount = 0; starCount < 25; starCount++)
	//{
	//	DeleteGO(m_star[starCount]);
	//}

	//for earch
	for (auto star : m_star) {
		DeleteGO(star);
	}

	////プレイヤーを削除する。
	//DeleteGO(player);
	////ゲームカメラを削除する。
	//DeleteGO(gameCamera);
	////ゲーム中のBGMを削除する。
	//DeleteGO(gameBGM);
	////背景を削除する。
	//DeleteGO(backGround);
}

bool Game::Start()
{

	LevelInit();

	//スコア
	m_score = NewGO<Score>(0, "score");

	//タイマー
	m_gameTimer = NewGO<GameTimer>(0, "timer");

	return true;
}

//更新処理。
void Game::Update()
{
	//if (player->starCount == 5)
	//{
	//	player->starCount = 0;
	//	DeleteGO(this);
	//	NewGO<GameClear>(0);
	//}
}

void Game::LevelInit()
{

	m_levelRender.Init("Assets/Level/StageLevel.tkl", [&](LevelObjectData& objData) {

		//バックグラウンド
		if (objData.EqualObjectName(L"moon") == true) {
			m_backGround = NewGO<BackGround>(0, "background");
			m_backGround->GetTransform()->m_localPosition = objData.position;
			m_backGround->GetTransform()->m_localRotation = objData.rotation;
			m_backGround->GetTransform()->m_localScale = objData.scale;
			return true;
		}

		//スター
		if (objData.EqualObjectName(L"star") == true) {
			m_star[starSum] = NewGO<Star>(1, "star");
			m_star[starSum]->GetTransform()->m_localPosition = objData.position;
			m_star[starSum]->GetTransform()->m_localRotation = objData.rotation;
			m_star[starSum]->GetTransform()->m_localScale = objData.scale;

			starSum++;
			return true;
		}

		});


}
