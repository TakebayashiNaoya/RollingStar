#include "stdafx.h"
#include "SpriteManager.h"

namespace
{
	const Vector2 FULL_HD_SIZE = { 1920.0f, 1080.0f };
	const Vector2 WINDOW_SIZE = { 1280.0f,900.0f };
	const Vector2 LOADING_VIEW_STAR_SIZE = { 120.0f,120.0f };
	const Vector2 GAME_VIEW_STAR_SIZE = { 50.0f,50.0f };
	const Vector2 RANKING_SIZE = { 500.0f, 100.0f };
	const Vector2 CROWN_SIZE = { 100.0f,100.0f };
	const Vector2 PUSH_A_SIZE = { 600.0f, 100.0f };

	const std::string SPRITE_FILE_PATH = "Assets/sprite/";
	const std::string EXTENSION_DDS = ".dds";

	struct SpriteOption
	{
		const std::string fileName;
		const Vector2 viewSize;

		/// <summary>
		/// ファイルのフルパスを取得します。
		/// </summary>
		/// <returns>MODEL_DATA_FILE_PATH と fileName を連結したファイルのフルパスを std::string 型で返します。</returns>
		std::string GetFullPath() const
		{
			return SPRITE_FILE_PATH + fileName + EXTENSION_DDS;
		}
	};

	const SpriteOption SPRITE_OPTIONS[] =
	{
		{"title", FULL_HD_SIZE},
		{"LoadingView",FULL_HD_SIZE},
		{"neonNormalStar",LOADING_VIEW_STAR_SIZE},
		{"neonGreenStar",LOADING_VIEW_STAR_SIZE},
		{"neonBlueStar",LOADING_VIEW_STAR_SIZE},
		{"neonPurpleStar",LOADING_VIEW_STAR_SIZE},
		{"neonOrangeStar",LOADING_VIEW_STAR_SIZE},
		{"neonRedStar",LOADING_VIEW_STAR_SIZE},
		{"tutorial",WINDOW_SIZE},
		{ "count3",FULL_HD_SIZE },
		{"count2",FULL_HD_SIZE},
		{"count1",FULL_HD_SIZE},
		{"countStart",FULL_HD_SIZE},
		{"redStar",GAME_VIEW_STAR_SIZE},
		{"orangeStar",GAME_VIEW_STAR_SIZE},
		{"purpleStar",GAME_VIEW_STAR_SIZE},
		{"blueStar",GAME_VIEW_STAR_SIZE},
		{"greenStar",GAME_VIEW_STAR_SIZE},
		{"normalStar",GAME_VIEW_STAR_SIZE},
		{"end",FULL_HD_SIZE},
		{"result",WINDOW_SIZE},
		{"backBlack",WINDOW_SIZE},
		{"ranking",RANKING_SIZE},
		{"goldCrown",CROWN_SIZE},
		{"silverCrown",CROWN_SIZE},
		{"bronzeCrown",CROWN_SIZE},
		{"pushAtoTitle",PUSH_A_SIZE},
	};

}

void SpriteManager::SpriteInit(SpriteRender& a, int b)
{
	a.Init(SPRITE_OPTIONS[b].GetFullPath().c_str(), SPRITE_OPTIONS[b].viewSize.x, SPRITE_OPTIONS[b].viewSize.y);
}
