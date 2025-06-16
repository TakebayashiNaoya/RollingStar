#include "stdafx.h"
#include "Star.h"
#include "BackGround.h"
#include "Transform.h"
#include "Player.h"
#include "Score.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Star::Star()
{
	m_transform = new Transform;
}

Star::~Star()
{
	delete m_transform;
}

bool Star::Start()
{
	m_backGround = FindGO<BackGround>("background");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");
	m_game = FindGO<Game>("game");
	m_transform->SetParent(m_backGround->GetTransform());
	m_modelRender.Init("Assets/modelData/star.tkm");
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	//スター効果音
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/star.wav");


	return true;
}

void Star::Update()
{
	m_transform->UpdateTransform();

	m_modelRender.SetPosition(m_transform->m_position);
	m_modelRender.SetRotation(m_transform->m_rotation);
	m_modelRender.SetScale(m_transform->m_scale);

	m_modelRender.Update();

	Vector3 playerPosition = m_player->m_position;
	Vector3 starPosition = m_transform->m_position;
	Vector3 diff = starPosition - playerPosition;

	//プレイヤーと☆の距離が150.0fより小さかったら。
	const float distnce = diff.Length();
	if (distnce <= 150.0f)
	{
		//スター効果音
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);
		se->SetVolume(3.5f);

		//自身(☆)を削除する。
		DeleteGO(this);

		if (m_game->m_gameEndFlag == false) {
			//取得数をカウント
			m_score->m_counter++;
		}
	}
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}