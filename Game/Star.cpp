#include "stdafx.h"
#include "Star.h"
#include "BackGround.h"
#include "Transform.h"
#include"Player.h"
#include"Score.h"

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
	m_transform->SetParent(m_backGround->GetTransform());
	m_modelRender.Init("Assets/modelData/star.tkm");
	//m_position.y = 3050.0f;
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

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
		//自身(☆)を削除する。
		DeleteGO(this);

		//取得数をカウント
		m_score->m_counter++;
	}
}

void Star::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}