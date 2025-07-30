#include "stdafx.h"
#include "CountDown.h"
#include "SoundManager.h"
#include "Game.h"
#include "SpriteManager.h"

namespace
{
	struct CountDownData
	{
		const float targetTime;
		SpriteRender* spriteRender;
	};
}

CountDown::CountDown()
{
	SpriteManager* spriteManager = FindGO<SpriteManager>("spritemanager");

	for (int count = enCount_Three; count < enCount_Num; count++)
	{
		spriteManager->SpriteInit(m_countSpriteRender[count], enSpriteKinds_CountThree + count);
	}
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
		{1.0f, &m_countSpriteRender[enCount_Three]},
		{2.0f, &m_countSpriteRender[enCount_Two]},
		{3.0f, &m_countSpriteRender[enCount_One]},
		{4.0f, &m_countSpriteRender[enCount_Start]},
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