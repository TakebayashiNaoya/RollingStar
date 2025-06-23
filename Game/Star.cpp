#include "stdafx.h"
#include "Star.h"
#include "BackGround.h"
#include "Transform.h"
#include "Player.h"
#include "Score.h"
#include "Game.h"
#include "StarSpawner.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Star::Star()
{
}

Star::~Star()
{
}

bool Star::Start()
{
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");
	m_game = FindGO<Game>("game");
	m_modelRender.Init("Assets/modelData/star.tkm");
	m_modelRender.Update();

	//�X�^�[���ʉ�
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/star.wav");

	return true;
}

void Star::Update()
{
	m_modelRender.SetTRS(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale);
	m_modelRender.Update();

	GetStar();
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Star::GetStar()
{
	Vector3 playerPosition = m_player->m_position;
	Vector3 starPosition = m_position;
	Vector3 diff = starPosition - playerPosition;

	//�v���C���[�Ɓ��̋�����150.0f��菬����������B
	const float distnce = diff.Length();
	if (distnce <= 150.0f)
	{
		//�X�^�[���ʉ�
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(2);
		se->Play(false);
		se->SetVolume(3.5f);

		//���g(��)���폜����B
		DeleteGO(this);

		if (m_game->m_gameEndFlag == false) {
			//�擾�����J�E���g
			m_score->m_counter++;
		}
	}
}
