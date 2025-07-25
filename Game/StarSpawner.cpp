#include "stdafx.h"
#include "StarSpawner.h"
#include "BackGround.h"
#include "Star.h"
#include "Transform.h"

namespace
{
	const float RESPAWN_TIME = 3.0f;
}

StarSpawner::StarSpawner()
{
	m_transform = new Transform;
}

StarSpawner::~StarSpawner()
{
	delete m_transform;
}

bool StarSpawner::Start()
{
	BackGround* bgIns = FindGO<BackGround>("background");
	m_transform->SetParent(bgIns->GetTransform());

	//親が複数おり、スター側からFindGOしてSetTransformできないため。
	m_star = NewGO<Star>(0, "star");
	m_star->SetTransform(m_transform);

	return true;
}

void StarSpawner::Update()
{
	if (m_star == nullptr)
	{
		m_respawnTimer += g_gameTime->GetFrameDeltaTime();
		if (m_respawnTimer >= RESPAWN_TIME)
		{
			m_star = NewGO<Star>(0, "star");
			m_star->SetTransform(m_transform);
			m_respawnTimer = 0.0f;	//リセット
		}
	}
	else if (m_star->GetIsDead())
	{
		DeleteGO(m_star);
		m_star = nullptr;
	}

	m_transform->UpdateTransform();
}