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
	const float GET_STAR_LENGTH = 200.0f;	// スターを消滅させるプレイヤーとの距離。
	const float ROTATION_SPEED = 5.0f;		// スターの自転速度。

	const int PERCENT_SCALE = 100;			// 色の出現確立を計算するとき、0～99で抽選するためにこの数値を使います。

	/// <summary>
	/// スターの種類ごとの色の出現確率(%)を定義する定数配列です。
	/// </summary>
	const int COLOR_PROBABILITIES[enStarKinds_Num] =
	{
		1,		// レッドスター。
		5,		// オレンジスター。
		10,		// パープルスター。
		15,		// ブルースター。
		30,		// グリーンスター。
		100		// ノーマルスター。
	};

	std::string MODEL_DATA_FILE_PATH = "Assets/modelData/";		// モデルデータのファイルパス。
	std::string EXTENSION_TKM = ".tkm";							// モデルデータの拡張子。

	/// <summary>
	/// モデルデータファイルのオプションを管理する構造体です。
	/// </summary>
	struct ModelOption
	{
		std::string fileName;	// ファイルパス。

		/// <summary>
		/// ファイルのフルパスを取得します。
		/// </summary>
		/// <returns>MODEL_DATA_FILE_PATH と fileName を連結したファイルのフルパスを std::string 型で返します。</returns>
		std::string GetFullPath() const
		{
			return MODEL_DATA_FILE_PATH + fileName + EXTENSION_TKM;
		}
	};

	/// <summary>
	/// スターのモデルのファイル名を定義する定数配列です。
	/// </summary>
	const ModelOption MODEL_LIST[] =
	{
		{"redStar"},
		{"orangeStar"},
		{"purpleStar"},
		{"blueStar"},
		{"greenStar"},
		{"normalStar"}
	};
};

bool Star::Start()
{
	m_popScoreManager = FindGO<PopScoreManager>("popscoremanager");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");
	m_game = FindGO<Game>("game");

	SetupStarColor();
	m_modelRender.Init(MODEL_LIST[m_starColor].GetFullPath().c_str());

	return true;
}

void Star::Update()
{
	m_modelRender.SetTRS(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale);
	Rotation();
	m_modelRender.Update();

	StarGet();
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Star::SetupStarColor()
{
	const int rnd = rand() % PERCENT_SCALE;

	for (int starKind = 0; starKind < enStarKinds_Num; starKind++)
	{
		if (rnd < COLOR_PROBABILITIES[starKind])
		{
			m_starColor = starKind;
			break;
		}
	}
}

void Star::StarGet()
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
	m_rotation.AddRotationDegY(ROTATION_SPEED);
	m_modelRender.SetRotation(m_rotation);
}

