#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
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

	//ゲームBGM
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/inGame.wav");

	//ゲームBGMを流す
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(1);
	m_gameBGM->Play(true);//ループ再生
	m_gameBGM->SetVolume(0.5f);
}

Game::~Game()
{
	for (auto star : FindGOs<Star>("star")) {
		DeleteGO(star);
	}
}

bool Game::Start()
{
	LevelInit();

	//スコア
	m_score = NewGO<Score>(0, "score");

	//リザルトビュー
	m_resultView = NewGO<ResultView>(0, "resultview");

	//ゲームタイマー
	m_gameTimer = FindGO<GameTimer>("gametimer");

	return true;
}

//更新処理。
void Game::Update()
{
	if (m_gameTimer->m_timeLimit < 0 or m_score->m_counter == m_starSum) {
		m_gameEndFlag = true;
		m_resultView->m_isFlag = true;
	}
}

void Game::LevelInit()
{
	//レベルイニット
	m_levelRender.Init("Assets/Level/StageLevel.tkl", [&](LevelObjectData& objData) {

		//月
		if (objData.EqualObjectName(L"moon") == true) {
			m_backGround = NewGO<BackGround>(0, "background");
			m_backGround->GetTransform()->m_localPosition = objData.position;
			m_backGround->GetTransform()->m_localRotation = objData.rotation;
			m_backGround->GetTransform()->m_localScale = objData.scale;
			return true;
		}

		//スター
		if (objData.EqualObjectName(L"star") == true) {
			m_star[m_starSum] = NewGO<Star>(1, "star");
			m_star[m_starSum]->GetTransform()->m_localPosition = objData.position;
			m_star[m_starSum]->GetTransform()->m_localRotation = objData.rotation;
			m_star[m_starSum]->GetTransform()->m_localScale = objData.scale;

			m_starSum++;
			return true;
		}
		});
}