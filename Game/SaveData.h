#pragma once
#include "Type.h"

class SaveData :public IGameObject
{
public:
	SaveData();
	~SaveData();
	bool Start();
	void Update();
	void Render(RenderContext& rc) {}

	void Seriarize();
	void Deserialize();

	std::vector<int> m_scoreRankList;
};

