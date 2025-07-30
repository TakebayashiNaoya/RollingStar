#pragma once

enum EnSpriteKinds
{
	enSpriteKinds_Title,
	enSpriteKinds_LoadingView,
	enSpriteKinds_NeonNormalStar,
	enSpriteKinds_NeonGreenStar,
	enSpriteKinds_NeonBlueStar,
	enSpriteKinds_NeonPurpleStar,
	enSpriteKinds_NeonOrangeStar,
	enSpriteKinds_NeonRedStar,
	enSpriteKinds_Tutorial,
	enSpriteKinds_CountThree,
	enSpriteKinds_CountTwo,
	enSpriteKinds_CountOne,
	enSpriteKinds_CountStart,
	enSpriteKinds_RedStar,
	enSpriteKinds_OrangeStar,
	enSpriteKinds_PurpleStar,
	enSpriteKinds_BlueStar,
	enSpriteKinds_GreenStar,
	enSpriteKinds_NormalStar,
	enSpriteKinds_End,
	enSpriteKinds_Result,
	enSpriteKinds_BackBlack,
	enSpriteKinds_Ranking,
	enSpriteKinds_GoldCrown,
	enSpriteKinds_SilverCrown,
	enSpriteKinds_BronzeCrown,
	enSpriteKinds_PushAtoTitle,
};

class SpriteManager : public IGameObject
{
public:
	void SpriteInit(SpriteRender& a, int b);
};

