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

ResultView::~ResultView()
{
	DeleteGO(m_game);
}

bool ResultView::Start()
{
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_backSpriteRender.Init("Assets/sprite/result.dds", 1280.0f, 900.0f);
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//�{�^��SE
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/result.wav");	//����SE
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/end.wav");		//�I���T�E���h

	m_spriteRender = &m_endSpriteRender;

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

		//�^�C���A�b�v����3�b��Ƀ��U���g�\��
		finishCount += g_gameTime->GetFrameDeltaTime();
		if (finishCount >= 3.0f) { m_spriteState = 1; }

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

			/// <summary>
			/// �t�H���g�ݒ�B
			/// </summary>
			/// {�\���������ϐ�(int�̂�) , x���W , y���W , �T�C�Y , �F}
			FontOption text[Font_Num];
			text[totalScore] = { m_score->m_totalScore,-250.0f,230.0f,4.0f,g_vec4White };
			text[redStar] = { m_score->m_redStarCount,410.0f,-160.0f,2.0f,g_vec4White };
			text[orangeStar] = { m_score->m_orangeStarCount,0.0f,-160.0f,2.0f,g_vec4White };
			text[purpleStar] = { m_score->m_purpleStarCount,-360.0f,-160.0f,2.0f,g_vec4White };
			text[blueStar] = { m_score->m_blueStarCount,410.0f,-20.0f,2.0f,g_vec4White };
			text[greenStar] = { m_score->m_greenStarCount,0.0f,-20.0f,2.0f,g_vec4White };
			text[normalStar] = { m_score->m_normalStarCount,-360.0f,-20.0f,2.0f,g_vec4White };

			for (int i = 0; i < Font_Num; i++)
			{
				wchar_t tmp[256];
				swprintf_s(tmp, 256, L"%d", text[i].data);
				m_fontRender[i].SetText(tmp);										//�e�L�X�g�\��
				m_fontRender[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0 });	//���W
				m_fontRender[i].SetScale(text[i].scale);							//�T�C�Y
				m_fontRender[i].SetColor(text[i].textColor);						//�F
			}


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

		for (int i = 0; i < Font_Num; i++)
		{
			m_fontRender[i].Draw(rc);
		}
	}
}

