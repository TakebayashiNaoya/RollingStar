#include "stdafx.h"
#include "SaveData.h"
#include "json.hpp"
#include <iostream>
#include <fstream>

namespace
{
	constexpr const char* SAVE_DATA_FILE_PATH = "Assets/saveData/saveData.json";
}

SaveData::SaveData()
{
	m_scoreRankList.clear();
}

SaveData::~SaveData()
{
	Deserialize();
}

bool SaveData::Start()
{
	Seriarize();

	return true;
}

void SaveData::Seriarize()
{
	std::ifstream file(SAVE_DATA_FILE_PATH);
	if (!file.is_open()) return;

	nlohmann::json jsonRoot;
	file >> jsonRoot;

	if (!jsonRoot.contains("resultScore"))
	{
		return;
	}

	auto resultScore = jsonRoot["resultScore"];
	for (auto& score : resultScore)
	{
		m_scoreRankList.push_back(score["score"]);
	}
}

void SaveData::Deserialize()
{
	std::ofstream file(SAVE_DATA_FILE_PATH);

	nlohmann::json resultScore;
	for (auto& score : m_scoreRankList)
	{
		nlohmann::json s;
		s["score"] = score;
		resultScore.push_back(s);
	}

	nlohmann::json jsonRoot;
	jsonRoot["resultScore"] = resultScore;

	file << jsonRoot.dump(4);  // 4 はインデント（見やすくする）
	file.close();
}