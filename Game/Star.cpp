#include "stdafx.h"
#include "Star.h"
#include "Transform.h"
#include "Player.h"
#include "Score.h"
#include "Game.h"
#include "Type.h"
#include "PopScoreManager.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

namespace {
	const float GET_STAR_LENGTH = 200.0f;
};

Star::~Star()
{
}

bool Star::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");
	m_game = FindGO<Game>("game");

	SetStarColor();
	SetInit();

	//スター効果音
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/star.wav");

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


/// <summary>
/// スターカラー確率
/// </summary>
void Star::SetStarColor()
{
	if (rand() % 100 < 1) { starColor = enStarKinds_Red; }
	else if (rand() % 100 < 5) { starColor = enStarKinds_Orange; }
	else if (rand() % 100 < 10) { starColor = enStarKinds_Purple; }
	else if (rand() % 100 < 15) { starColor = enStarKinds_Blue; }
	else if (rand() % 100 < 30) { starColor = enStarKinds_Green; }
	else { starColor = enStarKinds_Normal; }
}

/// <summary>
/// スターのカラー毎の設定
/// </summary>
void Star::SetInit()
{
	switch (starColor)
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

/// <summary>
/// スター取得の処理
/// </summary>
void Star::GetStar()
{
	Vector3 diff = m_transform->m_position - m_player->m_position;

	if (m_game->m_gameStartFlag) {
		//プレイヤーと☆の距離が150.0fより小さかったら。
		const float distnce = diff.Length();
		if (distnce <= GET_STAR_LENGTH)
		{
			GetStarSE();		//スター取得SE

			GetStarCounter();	//スター取得カウント

			isDead = true;		//スポナーにスターが消えたことを伝える

			m_popScoreManager->isPopFlag = true;//スコアをポップさせる
			m_popScoreManager->colorChecker = starColor;
		}
	}
}

/// <summary>
/// スター取得のSE
/// </summary>
void Star::GetStarSE()
{
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(2);
	se->Play(false);
	se->SetVolume(3.5f);
}

/// <summary>
/// スター取得カウント
/// </summary>
void Star::GetStarCounter()
{
	if (m_game->m_gameEndFlag == false)
	{
		switch (starColor)
		{
		case enStarKinds_Red:
			m_score->m_starCount[enStarKinds_Red]++;
			break;
		case enStarKinds_Orange:
			m_score->m_starCount[enStarKinds_Orange]++;
			break;
		case enStarKinds_Purple:
			m_score->m_starCount[enStarKinds_Purple]++;
			break;
		case enStarKinds_Blue:
			m_score->m_starCount[enStarKinds_Blue]++;
			break;
		case enStarKinds_Green:
			m_score->m_starCount[enStarKinds_Green]++;
			break;
		case enStarKinds_Normal:
			m_score->m_starCount[enStarKinds_Normal]++;
			break;
		}
	}
}

void Star::Rotation()
{
	m_rotation.AddRotationDegY(5.0f);
	m_modelRender.SetRotation(m_rotation);
}

