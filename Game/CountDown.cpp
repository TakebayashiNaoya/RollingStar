#include "stdafx.h"
#include "CountDown.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

CountDown::CountDown()
{
	//�J�E���g�_�E���̉摜
	m_count3SpriteRender.Init("Assets/sprite/count3.dds", 1920.0f, 1080.0f);			//�J�E���g�_�E��3
	m_count2SpriteRender.Init("Assets/sprite/count2.dds", 1920.0f, 1080.0f);			//�J�E���g�_�E��2
	m_count1SpriteRender.Init("Assets/sprite/count1.dds", 1920.0f, 1080.0f);			//�J�E���g�_�E��1
	m_countStartSpriteRender.Init("Assets/sprite/countStart.dds", 1920.0f, 1080.0f);	//�J�E���g�_�E���X�^�[�g

	m_spriteRender = &m_count3SpriteRender;

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/countDownStart.wav");//�J�E���g�_�E���J�n�̉�
}

CountDown::~CountDown()
{
	m_game->m_gameStartFlag = true;
}

bool CountDown::Start()
{
	//�J�E���g�_�E���J�n�̉�
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(4);
	se->Play(false);
	se->SetVolume(3.5f);

	m_game = FindGO<Game>("game");
	return true;
}

void CountDown::Update()
{
	countDown += g_gameTime->GetFrameDeltaTime();		//�b���J�E���g

	if (countDown >= 0.0f and countDown < 1.0f) {		//3
		m_spriteRender = &m_count3SpriteRender;
	}
	else if (countDown >= 1.0f and countDown < 2.0f) {	//2
		m_spriteRender = &m_count2SpriteRender;
	}
	else if (countDown >= 2.0f and countDown < 3.0f) {	//1
		m_spriteRender = &m_count1SpriteRender;
	}
	else if (countDown >= 3.0f and countDown < 4.0f) {	//�X�^�[�g
		m_spriteRender = &m_countStartSpriteRender;
	}
	else if (countDown >= 4.0f) {						//�C���Q�[����
		DeleteGO(this);
	}

}

void CountDown::Render(RenderContext& rc)
{
	m_spriteRender->Draw(rc);
}