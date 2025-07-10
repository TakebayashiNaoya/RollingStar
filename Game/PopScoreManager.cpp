#include "stdafx.h"
#include "PopScoreManager.h"

#include "PopScore.h"

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
