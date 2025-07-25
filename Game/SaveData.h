/// <summary>
/// セーブデータを管理するクラス
/// </summary>
#pragma once
#include "Type.h"

class SaveData :public IGameObject
{
public:
	SaveData();
	~SaveData();

	std::vector<int> m_scoreRankList;

private:
	bool Start()override final;
	void Render(RenderContext& rc)override final {}

	void Seriarize();
	void Deserialize();
};

