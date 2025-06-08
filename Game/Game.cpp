#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "sound/SoundEngine.h"
#include "Star.h"
#include "Transform.h"
#include "Score.h"
#include "GameTimer.h"
#include "ResultView.h"

Game::Game()
{
	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
}

Game::~Game()
{
	for (auto star : m_star) {
		DeleteGO(star);
	}
}

bool Game::Start()
{
	LevelInit();

	//スコア
	m_score = NewGO<Score>(0, "score");

	//タイマー
	m_gameTimer = NewGO<GameTimer>(0, "timer");

	//リザルトビュー
	m_resultView = NewGO<ResultView>(0, "resultview");

	return true;
}

//更新処理。
void Game::Update()
{
	if (m_gameTimer->m_timeLimit <= 0 or m_score->m_counter == starSum) {
		finishTime = m_gameTimer->m_timeLimit;
		finishScore = m_score->m_counter;
		m_resultView->m_isFlag = true;
		DeleteGO(m_score);
		DeleteGO(m_gameTimer);
	}
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
