#pragma once
class Game;
class GameTimer :public IGameObject
{
public:
	GameTimer();
	~GameTimer();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	//�����o�ϐ�
	Game* m_game;
	FontRender m_fontRender;
	float m_maxTimer = 5.0f;	//��������
	float m_timer = 0.0f;		//�^�C�}�[
	float m_timeLimit = 0.0f;	//�^�C�����~�b�g
};