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
#include "StarSpawner.h"
#include "PopScoreManager.h"

Game::Game()
{

}

Game::~Game()
{
	for (auto star : FindGOs<Star>("star")) {
		DeleteGO(star);
	}
	for (auto starSpawner : FindGOs<StarSpawner>("starspawner")) {
		DeleteGO(starSpawner);
	}

	DeleteGO(m_popScoreManager);
	DeleteGO(m_gameBGM);
	DeleteGO(m_backGround);
	DeleteGO(m_gameTimer);
	DeleteGO(m_score);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
}

bool Game::Start()
{
	//空を作る。
	InitSky();

	//ポップスコアマネージャーを起動。
	m_popScoreManager = NewGO<PopScoreManager>(0, "popscoremanager");

	//プレイヤーのオブジェクトを作る。
	m_player = NewGO<Player>(0, "player");

	//ゲームカメラのオブジェクトを作る。
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	LevelInit();

	//スコア
	m_score = NewGO<Score>(0, "score");

	//リザルトビュー
	m_resultView = NewGO<ResultView>(0, "resultview");

	//ゲームタイマー
	m_gameTimer = FindGO<GameTimer>("gametimer");

	//ゲームBGM
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/inGame.wav");

	//ゲームBGMを流す
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(1);
	m_gameBGM->Play(true);//ループ再生
	m_gameBGM->SetVolume(0.5f);

	return true;
}

//更新処理。
void Game::Update()
{
	if (m_gameTimer->m_timeLimit < 0) {
		m_gameStartFlag = false;
		m_gameEndFlag = true;
		m_resultView->m_isFlag = true;
	}
}

void Game::LevelInit()
{
	bool is = false;
	//レベルイニット
	m_levelRender.Init("Assets/Level/StageLevel2.tkl", [&](LevelObjectData& objData) {

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
			if (is) {

				//return true;
			}
			is = true;
			m_starSpawner[m_starSum] = NewGO<StarSpawner>(1, "starspawner");
			m_starSpawner[m_starSum]->GetTransform()->m_localPosition = objData.position;
			m_starSpawner[m_starSum]->GetTransform()->m_localRotation = objData.rotation;
			m_starSpawner[m_starSum]->GetTransform()->m_localScale = objData.scale;

			m_starSum++;
			return true;
		}
		});
}

void Game::InitSky()
{
	//現在の空を破棄。
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetPosition(m_skyCubePos);

	//環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}
