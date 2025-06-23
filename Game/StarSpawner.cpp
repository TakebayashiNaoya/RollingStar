#include "stdafx.h"
#include "StarSpawner.h"
#include "Star.h"
#include "Transform.h"
#include "BackGround.h"

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

	Star* star = NewGO<Star>(0, "star");
	star->SetTransform(m_transform);

	return true;
}

void StarSpawner::Update()
{
	/*if (isStarDeath == true) {
		NewGO<Star>(0, "star");
	}*/

	m_transform->UpdateTransform();
	m_modelRender.SetTRS(m_transform->m_position, m_transform->m_rotation, m_transform->m_scale);
	m_modelRender.Update();
}

void StarSpawner::Render(RenderContext& rc)
{
}