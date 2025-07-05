#pragma once
class GameLoding :public IGameObject
{
public:
	GameLoding();
	~GameLoding();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc) override;

};

