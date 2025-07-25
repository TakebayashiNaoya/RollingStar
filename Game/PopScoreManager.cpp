#include "stdafx.h"
#include "PopScoreManager.h"
#include "PopScore.h"

void PopScoreManager::Update()
{
	if (isPopFlag)
	{
		NewGO<PopScore>(0, "popscore");
		isPopFlag = false;
	}
}
