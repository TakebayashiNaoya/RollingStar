#include "stdafx.h"
#include "CountDown.h"
#include "SoundManager.h"
#include "Game.h"

namespace
{
	struct CountDownData
	{
		const float targetTime;
		SpriteRender* spriteRender;

		CountDownData(const float time, SpriteRender* render)
			: targetTime(time)
			, spriteRender(render)
		{
		}
	};
}

CountDown::CountDown()
{
	// カウントダウンの画像を初期化します。
	m_countThreeSpriteRender.Init("Assets/sprite/count3.dds", 1920.0f, 1080.0f);
	m_countTwoSpriteRender.Init("Assets/sprite/count2.dds", 1920.0f, 1080.0f);
	m_countOneSpriteRender.Init("Assets/sprite/count1.dds", 1920.0f, 1080.0f);
	m_countStartSpriteRender.Init("Assets/sprite/countStart.dds", 1920.0f, 1080.0f);

	m_spriteRender = &m_countThreeSpriteRender;
}

CountDown::~CountDown()
{
	m_game->SetGameStartFlag(true);
}

bool CountDown::Start()
{
	SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
	soundManager->SoundNewGO(enSoundList_CountDownSE);

	m_game = FindGO<Game>("game");
	return true;
}

void CountDown::Update()
{
	countDown += g_gameTime->GetFrameDeltaTime();

	SpriteRender* spriteRender = ComputeSpriteRender();
	if (spriteRender == nullptr)
	{
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
	CountDownData dataList[] =
	{
		CountDownData(1.0f, &m_countThreeSpriteRender),
		CountDownData(2.0f, &m_countTwoSpriteRender),
		CountDownData(3.0f, &m_countOneSpriteRender),
		CountDownData(4.0f, &m_countStartSpriteRender),
	};

	for (CountDownData& data : dataList)
	{
		if (countDown < data.targetTime)
		{
			return data.spriteRender;
		}
	}
	return nullptr;
}