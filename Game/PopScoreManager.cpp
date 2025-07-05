#include "stdafx.h"
#include "PopScoreManager.h"
#include "PopScore.h"

PopScoreManager::PopScoreManager()
{
}

PopScoreManager::~PopScoreManager()
{
}

bool PopScoreManager::Start()
{
	return true;
}

void PopScoreManager::Update()
{
	if (isPopFlag) {
		NewGO<PopScore>(0, "popscore");
		isPopFlag = false;
	}
}

void PopScoreManager::Render(RenderContext& rc)
{
}
