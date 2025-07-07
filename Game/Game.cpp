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
#include "LoadingView.h"

namespace
{
	// 1フレームにNewGOできる数
	const int MAX_NEWGO_COUNT = 5;
}

Game::Game()
{
	//スタースポナーとレベルオブジェクトを初期化
	m_starSpawners.clear();
	m_levelObjectDataList.clear();
}

Game::~Game()
{
	//スタースポナーと残っている星をデリート
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
	switch (m_gameNewGOType)
	{
	case enGameNewGOType_Init:
	{
		InitLevelObjectDataList();

		m_loadingView = FindGO<LoadingView>("loadingview");
		//ロード1/6到達
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_1] = true;

		m_gameNewGOType = enGameNewGOType_Step1;

		return false;
	}
	case enGameNewGOType_Step1:
	{
		InitSky();
		m_popScoreManager = NewGO<PopScoreManager>(0, "popscoremanager");
		m_player = NewGO<Player>(0, "player");
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
		m_score = NewGO<Score>(0, "score");
		m_resultView = NewGO<ResultView>(0, "resultview");

		//制限時間を取得するためにゲームタイマーをFindGO
		m_gameTimer = NewGO<GameTimer>(0, "gametimer");

		//ゲームBGM
		g_soundEngine->ResistWaveFileBank(1, "Assets/sound/inGame.wav");
		m_gameBGM = NewGO<SoundSource>(0);
		m_gameBGM->Init(1);
		m_gameBGM->Play(true);
		m_gameBGM->SetVolume(0.5f);

		//ロード2/6到達
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_2] = true;

		m_gameNewGOType = EnGameNewGOType_Step2;
		return false;
	}
	case EnGameNewGOType_Step2:
	{
		//objDataのイニット進捗に応じて
		if (m_objDataListIndex < m_levelObjectDataList.size()) {
			for (int i = 0; i < MAX_NEWGO_COUNT; ++i) {
				if (m_objDataListIndex >= m_levelObjectDataList.size()) {
					break;
				}
				InitLevelObject(m_levelObjectDataList[m_objDataListIndex]);
				m_objDataListIndex++;
			}

			if (m_objDataListIndex > m_levelObjectDataList.size() / 4) {
				//ロード3/6到達
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_3] = true;
			}
			if (m_objDataListIndex > m_levelObjectDataList.size() / 4 * 2) {
				//ロード4/6到達
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_4] = true;
			}
			if (m_objDataListIndex > m_levelObjectDataList.size() / 4 * 3) {
				//ロード5/6到達
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_5] = true;
			}

			return false;
		}
		break;	// Stepが増えたらbreakを消す
	}
	}

	//ロード6/6到達
	m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_6] = true;

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

void Game::InitLevelObjectDataList()
{
	//レベルイニット
	m_levelRender.Init("Assets/Level/StageLevel2.tkl", [&](LevelObjectData& objData)
		{
			m_levelObjectDataList.push_back(objData);

			return true;
		});
}
void Game::InitLevelObject(LevelObjectData& objData)
{
	//月
	if (objData.EqualObjectName(L"moon") == true) {
		m_backGround = NewGO<BackGround>(0, "background");
		m_backGround->GetTransform()->m_localPosition = objData.position;
		m_backGround->GetTransform()->m_localRotation = objData.rotation;
		m_backGround->GetTransform()->m_localScale = objData.scale;
		return;
	}

	//スター
	if (objData.EqualObjectName(L"star") == true) {
		StarSpawner* starSpaner = NewGO<StarSpawner>(1, "starspawner");;
		starSpaner->GetTransform()->m_localPosition = objData.position;
		starSpaner->GetTransform()->m_localRotation = objData.rotation;
		starSpaner->GetTransform()->m_localScale = objData.scale;
		m_starSpawners.push_back(starSpaner);
		m_starSum++;
		return;
	}
}