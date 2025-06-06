#pragma once

class Star;
class Game;

class Score : public IGameObject
{
public:
	Score();
	~Score();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//ƒƒ“ƒo•Ï”
	FontRender m_fontRender;
	Star* m_star = nullptr;
	Game* m_game = nullptr;
	int m_counter = 0;
};

