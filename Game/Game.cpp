#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "LoadingView.h"
#include "Player.h"
#include "PopScoreManager.h"
#include "ResultView.h"
#include "Score.h"
#include "SoundManager.h"
#include "Star.h"
#include "StarSpawner.h"
#include "Transform.h"

namespace
{
	// 1フレームにNewGOできる数。
	const int MAX_NEWGO_COUNT = 5;

	// ロードの進捗を獲得する指標。
	const float LOADING_PERCENT_25 = 1.0f / 4.0f;
	const float LOADING_PERCENT_50 = 2.0f / 4.0f;
	const float LOADING_PERCENT_75 = 3.0f / 4.0f;
}

Game::Game()
{
	m_starSpawners.clear();
	m_levelObjectDataList.clear();
}

Game::~Game()
{
	for (auto star : FindGOs<Star>("star"))
	{
		DeleteGO(star);
	}

	for (auto starSpawner : FindGOs<StarSpawner>("starspawner"))
	{
		DeleteGO(starSpawner);
	}

	DeleteGO(m_backGround);
	DeleteGO(m_skyCube);
	DeleteGO(m_score);
	DeleteGO(m_player);
	DeleteGO(m_gameTimer);
	DeleteGO(m_gameCamera);
	DeleteGO(m_popScoreManager);

	SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
	soundManager->SoundDeleteGO(enSoundList_InGameBGM);
}

bool Game::Start()
{
	switch (m_gameNewGOType)
	{
	case enGameNewGOType_Init:
	{
		InitLevelObjectDataList();

		m_loadingView = FindGO<LoadingView>("loadingview");

		// ロード1/6を描画します。
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_First] = true;

		m_gameNewGOType = enGameNewGOType_Step1;

		return false;
	}
	case enGameNewGOType_Step1:
	{
		InitSky();

		SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
		soundManager->SoundNewGO(enSoundList_InGameBGM);

		m_score = NewGO<Score>(0, "score");
		m_player = NewGO<Player>(0, "player");
		m_gameTimer = NewGO<GameTimer>(0, "gametimer");
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
		m_resultView = NewGO<ResultView>(0, "resultview");
		m_popScoreManager = NewGO<PopScoreManager>(0, "popscoremanager");

		// ロード2/6を描画します。
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_Second] = true;

		m_gameNewGOType = EnGameNewGOType_Step2;
		return false;
	}
	case EnGameNewGOType_Step2:
	{
		// 全てのレベルオブジェクトを初期化し終わったらbreakします。
		if (m_objDataListIndex < m_levelObjectDataList.size())
		{
			// 5回ずつレベルオブジェクトを初期化し、一定数の初期化が終わった時点でロード画面の描画を挟みます。
			for (int i = 0; i < MAX_NEWGO_COUNT; ++i)
			{
				if (m_objDataListIndex >= m_levelObjectDataList.size())
				{
					break;
				}
				InitLevelObject(m_levelObjectDataList[m_objDataListIndex]);
				m_objDataListIndex++;
			}

			// ロード3/6を描画します。
			if (m_objDataListIndex > m_levelObjectDataList.size() * LOADING_PERCENT_25)
			{
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_Third] = true;
			}

			// ロード4/6を描画します。
			if (m_objDataListIndex > m_levelObjectDataList.size() * LOADING_PERCENT_50)
			{
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_Fourth] = true;
			}

			// ロード5/6を描画します。
			if (m_objDataListIndex > m_levelObjectDataList.size() * LOADING_PERCENT_75)
			{
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_Fifth] = true;
			}

			return false;
		}
		break;
	}
	}

	// ロード6/6を描画します。
	m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_Sixth] = true;

	return true;
}

void Game::Update()
{
	if (m_gameTimer->GetTimeLimit() < 0)
	{
		m_isGameStartFlag = false;
		m_isGameEndFlag = true;
	}
}

void Game::InitSky()
{
	// 現在の空を破棄します。
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetPosition(m_skyCubePos);

	// 環境光の計算のためのIBLテクスチャをセットします。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}

void Game::InitLevelObjectDataList()
{
	m_levelRender.Init("Assets/Level/StageLevel2.tkl", [&](LevelObjectData& objData)
		{
			m_levelObjectDataList.push_back(objData);

			return true;
		});
}
void Game::InitLevelObject(LevelObjectData& objData)
{
	if (objData.EqualObjectName(L"moon") == true)
	{
		m_backGround = NewGO<BackGround>(0, "background");
		m_backGround->GetTransform()->m_localPosition = objData.position;
		m_backGround->GetTransform()->m_localRotation = objData.rotation;
		m_backGround->GetTransform()->m_localScale = objData.scale;
		return;
	}

	if (objData.EqualObjectName(L"star") == true)
	{
		StarSpawner* starSpaner = NewGO<StarSpawner>(1, "starspawner");
		starSpaner->GetTransform()->m_localPosition = objData.position;
		starSpaner->GetTransform()->m_localRotation = objData.rotation;
		starSpaner->GetTransform()->m_localScale = objData.scale;
		m_starSpawners.push_back(starSpaner);
		return;
	}
}