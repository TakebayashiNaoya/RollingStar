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

Game::Game()
{

}

Game::~Game()
{
	/*for (auto starSpawner : FindGOs<StarSpawner>("starspawner")) {
		DeleteGO(starSpawner);
	}*/
	DeleteGO(m_starSpawner[161]);

	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_score);
	DeleteGO(m_gameTimer);
	DeleteGO(m_backGround);
	DeleteGO(m_gameBGM);

}

bool Game::Start()
{
	//�v���C���[�̃I�u�W�F�N�g�����B
	m_player = NewGO<Player>(0, "player");

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�Q�[��BGM
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/inGame.wav");

	//�Q�[��BGM�𗬂�
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(1);
	m_gameBGM->Play(true);//���[�v�Đ�
	m_gameBGM->SetVolume(0.5f);

	LevelInit();

	//�X�R�A
	m_score = NewGO<Score>(0, "score");

	//���U���g�r���[
	m_resultView = NewGO<ResultView>(0, "resultview");

	//�Q�[���^�C�}�[
	m_gameTimer = FindGO<GameTimer>("gametimer");

	return true;
}

//�X�V�����B
void Game::Update()
{
	if (m_gameTimer->m_timeLimit < 0 or m_score->m_counter == m_starSum) {
		m_gameEndFlag = true;
		m_resultView->m_isFlag = true;
	}
}

void Game::LevelInit()
{
	bool is = false;
	//���x���C�j�b�g
	m_levelRender.Init("Assets/Level/StageLevel2.tkl", [&](LevelObjectData& objData) {

		//��
		if (objData.EqualObjectName(L"moon") == true) {
			m_backGround = NewGO<BackGround>(0, "background");
			m_backGround->GetTransform()->m_localPosition = objData.position;
			m_backGround->GetTransform()->m_localRotation = objData.rotation;
			m_backGround->GetTransform()->m_localScale = objData.scale;
			return true;
		}

		//�X�^�[
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