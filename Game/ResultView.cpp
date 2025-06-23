#include "stdafx.h"
#include "ResultView.h"
#include "BackGround.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "Player.h"
#include "Score.h"
#include "Star.h"
#include "Title.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

ResultView::ResultView()
{

}

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_backSpriteRender.Init("Assets/sprite/backBlack.dds", 1280.0f, 720.0f);
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//�{�^��SE
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/result.wav");	//����SE
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/end.wav");		//�I���T�E���h

	m_spriteRender = &m_endSpriteRender;

	/*m_backGround = FindGO<BackGround>("background");
	m_gameCamera = FindGO<GameCamera>("gamecamera");
	m_player = FindGO<Player>("player");
	m_star = FindGO<Star>("star");*/

	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_score = FindGO<Score>("score");

	return true;
}

//�X�V�����B

void ResultView::Update()
{
	if (m_isFlag == true) {

		if (endState == 0) {
			//�I���T�E���h
			SoundSource* endSE = NewGO<SoundSource>(0);
			endSE->Init(5);
			endSE->Play(false);
			endSE->SetVolume(3.5f);
			endState = 1;	//�I���T�E���h��1�񂾂��炷
		}

		finishCount += g_gameTime->GetFrameDeltaTime();

		if (finishCount >= 3.0f) {
			m_spriteState = 1;
		}

		if (m_spriteState == 0) {
			m_spriteRender = &m_endSpriteRender;

		}
		else if (m_spriteState == 1) {
			m_spriteRender = &m_backSpriteRender;

			//����SE
			if (callState == 0) {
				SoundSource* callSE = NewGO<SoundSource>(0);
				callSE->Init(7);
				callSE->Play(false);
				callSE->SetVolume(3.5f);
				callState = 1;	//����SE��1�񂾂��炷
			}

			//���U���g�\��
			wchar_t wcsbuf[256];
			swprintf_s(wcsbuf, 256, L"�@�@�@�y���ʁz\n\n�@ �̂���^�C���@%d�b\n\n�@ �W�߂��X�^�[�@%d/%d\n\n�iA�j�������ă^�C�g����", int(m_gameTimer->m_timeLimit), m_score->m_counter, m_game->m_starSum);
			m_fontRender.SetText(wcsbuf);						//�`�悷��B
			m_fontRender.SetScale(2.0f);						//�����̃T�C�Y
			m_fontRender.SetPosition({ -550.0f,300.0f,0.0f });	//�\��������W��ݒ肷��B
			m_fontRender.SetColor(g_vec4White);					//�\������F��ݒ肷��B

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//�{�^��SE
				SoundSource* se = NewGO<SoundSource>(0);
				se->Init(6);
				se->Play(false);
				se->SetVolume(3.5f);

				//�^�C�g����
				m_title = NewGO<Title>(0, "title");
				//�Q�[���I��
				DeleteGO(this);
			}
		}
	}
}

//�`�揈���B
void ResultView::Render(RenderContext& rc)
{
	if (m_isFlag == true) {
		m_spriteRender->Draw(rc);
		m_fontRender.Draw(rc);
	}
}