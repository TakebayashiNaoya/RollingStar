#include "stdafx.h"
#include "CountDown.h"

#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

#include "Game.h"

namespace
{
	struct CountDownData
	{
		const float targetTime;
		SpriteRender* spriteRender;
		// 
		CountDownData(const float time, SpriteRender* render)
			: targetTime(time)
			, spriteRender(render)
		{
		}
	};
}

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
	m_game->SetGameStartFlag(true);
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
	countDown += g_gameTime->GetFrameDeltaTime();

	SpriteRender* spriteRender = ComputeSpriteRender();
	if (spriteRender == nullptr) {
		DeleteGO(this);
	}
	m_spriteRender = spriteRender;
}

void CountDown::Render(RenderContext& rc)
{
	m_spriteRender->Draw(rc);
}

SpriteRender* CountDown::ComputeSpriteRender()
{
	CountDownData dataList[] = {
		CountDownData(1.0f, &m_count3SpriteRender),
		CountDownData(2.0f, &m_count2SpriteRender),
		CountDownData(3.0f, &m_count1SpriteRender),
		CountDownData(4.0f, &m_countStartSpriteRender),
	};

	for (CountDownData& data : dataList) {
		if (countDown < data.targetTime) {
			return data.spriteRender;
		}
	}
	return nullptr;
}