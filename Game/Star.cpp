#include "stdafx.h"
#include "Star.h"
#include "SoundManager.h"
#include "Game.h"
#include "Player.h"
#include "PopScoreManager.h"
#include "Score.h"
#include "Transform.h"
#include "Type.h"

namespace
{
	const float GET_STAR_LENGTH = 200.0f;

	const int PERCENT_SCALE = 100;
	const int COLOR_PROBABILITY_RED = 1;
	const int COLOR_PROBABILITY_ORANGE = 5;
	const int COLOR_PROBABILITY_PURPLE = 10;
	const int COLOR_PROBABILITY_BLUE = 15;
	const int COLOR_PROBABILITY_GREEN = 30;
};

bool Star::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");
	m_game = FindGO<Game>("game");

	SetStarColor();
	StarModelInit();

	return true;
}

void Star::Update()
{
	m_modelRender.SetTRS(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale);
	Rotation();
	m_modelRender.Update();

	GetStar();
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}


///////////////////////////////////////////////////////////////////
// ここからメソッドまとめ。
///////////////////////////////////////////////////////////////////

void Star::SetStarColor()
{
	if (rand() % PERCENT_SCALE < COLOR_PROBABILITY_RED) { m_starColor = enStarKinds_Red; }
	else if (rand() % PERCENT_SCALE < COLOR_PROBABILITY_ORANGE) { m_starColor = enStarKinds_Orange; }
	else if (rand() % PERCENT_SCALE < COLOR_PROBABILITY_PURPLE) { m_starColor = enStarKinds_Purple; }
	else if (rand() % PERCENT_SCALE < COLOR_PROBABILITY_BLUE) { m_starColor = enStarKinds_Blue; }
	else if (rand() % PERCENT_SCALE < COLOR_PROBABILITY_GREEN) { m_starColor = enStarKinds_Green; }
	else { m_starColor = enStarKinds_Normal; }
}

void Star::StarModelInit()
{
	switch (m_starColor)
	{
	case enStarKinds_Red:
		m_modelRender.Init("Assets/modelData/redStar.tkm");
		break;
	case enStarKinds_Orange:
		m_modelRender.Init("Assets/modelData/orangeStar.tkm");
		break;
	case enStarKinds_Purple:
		m_modelRender.Init("Assets/modelData/purpleStar.tkm");
		break;
	case enStarKinds_Blue:
		m_modelRender.Init("Assets/modelData/blueStar.tkm");
		break;
	case enStarKinds_Green:
		m_modelRender.Init("Assets/modelData/greenStar.tkm");
		break;
	case enStarKinds_Normal:
		m_modelRender.Init("Assets/modelData/star.tkm");
		break;
	}
}

void Star::GetStar()
{
	Vector3 diff = m_transform->m_position - m_player->GetPosition();

	if (m_game->GetGameStartFlag())
	{
		const float distnce = diff.Length();
		if (distnce <= GET_STAR_LENGTH)
		{
			SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
			soundManager->SoundNewGO(enSoundList_StarGetSE);

			m_score->StarCountIncrease(m_starColor);

			m_isDead = true;
			m_popScoreManager->SetPopFlag(true);
			m_popScoreManager->SetColorChecker(m_starColor);
		}
	}
}

void Star::Rotation()
{
	m_rotation.AddRotationDegY(5.0f);
	m_modelRender.SetRotation(m_rotation);
}

