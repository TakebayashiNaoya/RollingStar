///
/// セーブデータを管理するクラス
///
#pragma once
#include "Type.h"

class SaveData :public IGameObject
{
public:
	SaveData();
	~SaveData();
	bool Start()override;
	void Render(RenderContext& rc)override {}

public:
	std::vector<int> m_scoreRankList;

private:
	void Seriarize();
	void Deserialize();
};

