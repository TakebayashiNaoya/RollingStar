#include "stdafx.h"
#include "Game.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "LoadingView.h"
#include "Player.h"
#include "PopScoreManager.h"
#include "ResultView.h"
#include "Score.h"
#include "Star.h"
#include "StarSpawner.h"
#include "Transform.h"

namespace
{
	// 1�t���[����NewGO�ł��鐔
	const int MAX_NEWGO_COUNT = 5;
}

Game::Game()
{
	//�X�^�[�X�|�i�[�ƃ��x���I�u�W�F�N�g��������
	m_starSpawners.clear();
	m_levelObjectDataList.clear();
}

Game::~Game()
{
	for (auto star : FindGOs<Star>("star")) {
		DeleteGO(star);
	}
	for (auto starSpawner : FindGOs<StarSpawner>("starspawner")) {
		DeleteGO(starSpawner);
	}
	DeleteGO(m_backGround);
	DeleteGO(m_skyCube);
	DeleteGO(m_gameBGM);
	DeleteGO(m_score);
	DeleteGO(m_player);
	DeleteGO(m_gameTimer);
	DeleteGO(m_gameCamera);
	DeleteGO(m_popScoreManager);
}

bool Game::Start()
{
	switch (m_gameNewGOType)
	{
	case enGameNewGOType_Init:
	{
		InitLevelObjectDataList();

		m_loadingView = FindGO<LoadingView>("loadingview");

		//���[�h1/6���B
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_1] = true;

		m_gameNewGOType = enGameNewGOType_Step1;

		return false;
	}
	case enGameNewGOType_Step1:
	{
		InitSky();
		InitBGM();
		m_score = NewGO<Score>(0, "score");
		m_player = NewGO<Player>(0, "player");
		m_gameTimer = NewGO<GameTimer>(0, "gametimer");
		m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
		m_resultView = NewGO<ResultView>(0, "resultview");
		m_popScoreManager = NewGO<PopScoreManager>(0, "popscoremanager");

		//���[�h2/6���B
		m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_2] = true;

		m_gameNewGOType = EnGameNewGOType_Step2;
		return false;
	}
	case EnGameNewGOType_Step2:
	{
		//objData�̃C�j�b�g�i���ɉ�����
		if (m_objDataListIndex < m_levelObjectDataList.size()) {
			for (int i = 0; i < MAX_NEWGO_COUNT; ++i) {
				if (m_objDataListIndex >= m_levelObjectDataList.size()) {
					break;
				}
				InitLevelObject(m_levelObjectDataList[m_objDataListIndex]);
				m_objDataListIndex++;
			}

			//���[�h3/6���B
			if (m_objDataListIndex > m_levelObjectDataList.size() / 4) {
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_3] = true;
			}

			//���[�h4/6���B
			if (m_objDataListIndex > m_levelObjectDataList.size() / 4 * 2) {
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_4] = true;
			}

			//���[�h5/6���B
			if (m_objDataListIndex > m_levelObjectDataList.size() / 4 * 3) {
				m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_5] = true;
			}

			return false;
		}
		break;
	}
	}

	//���[�h6/6���B
	m_loadingView->showLoadingPhases[LoadingView::EnLoadingPhase::enLoadingPhase_6] = true;

	return true;
}

//�X�V�����B
void Game::Update()
{
	if (m_gameTimer->GetTimeLimit() < 0) {
		m_isGameStartFlag = false;
		m_isGameEndFlag = true;
	}
}

///////////////////////////////////////////////////////////////////
// �������烁�\�b�h�܂Ƃ߁B
///////////////////////////////////////////////////////////////////

void Game::InitSky()
{
	//���݂̋��j���B
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	m_skyCube->SetPosition(m_skyCubePos);

	//�����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}

void Game::InitBGM()
{
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/inGame.wav");
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(1);
	m_gameBGM->Play(true);
	m_gameBGM->SetVolume(0.5f);
}

void Game::InitLevelObjectDataList()
{
	//���x���C�j�b�g
	m_levelRender.Init("Assets/Level/StageLevel2.tkl", [&](LevelObjectData& objData)
		{
			m_levelObjectDataList.push_back(objData);

			return true;
		});
}
void Game::InitLevelObject(LevelObjectData& objData)
{
	//��
	if (objData.EqualObjectName(L"moon") == true) {
		m_backGround = NewGO<BackGround>(0, "background");
		m_backGround->GetTransform()->m_localPosition = objData.position;
		m_backGround->GetTransform()->m_localRotation = objData.rotation;
		m_backGround->GetTransform()->m_localScale = objData.scale;
		return;
	}

	//�X�^�[
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