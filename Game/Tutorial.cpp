#include "stdafx.h"
#include "Tutorial.h"
#include "GameTimer.h"
#include "Game.h"
#include "CountDown.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Tutorial::Tutorial()
{

}

Tutorial::~Tutorial()
{
	m_countDown = NewGO<CountDown>(0, "countdown");
}

bool Tutorial::Start()
{
	m_spriteRender.Init("Assets/sprite/backBlack.dds", 1280.0f, 800.0f);//���w�i
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//�{�^��SE

	m_game = NewGO<Game>(0, "game");
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	return true;
}

void Tutorial::Update()
{
	//�`���[�g���A���\��
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"�@�@�@�@�y�V�ѕ��z\n\n���̏�̑���܂��\n\n���ׂẴX�^�[���W�߂܂��傤�I\n\n�X�^�[�͑S����%d����܂��B\n\n�������Ԃ�%d�b�ł��B\n\n�iA�j�������ăX�^�[�g�I", m_game->m_starSum, int(m_gameTimer->m_maxTimer));
	m_fontRender.SetText(wcsbuf);						//�`�悷��B
	m_fontRender.SetScale(1.5f);						//�����̃T�C�Y
	m_fontRender.SetPosition({ -480.0f,350.0f,0.0f });	//�\��������W��ݒ肷��B
	m_fontRender.SetColor(g_vec4White);					//�\������F��ݒ肷��B

	//A�������ăX�^�[�g
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�{�^��SE
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(6);
		se->Play(false);
		se->SetVolume(3.5f);

		DeleteGO(this);
	}
}

void Tutorial::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}