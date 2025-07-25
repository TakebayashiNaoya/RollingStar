/// <summary>
/// �C���Q�[���̎��Ԃ��Ǘ�����N���X
/// </summary>
#pragma once

class Game;

class GameTimer :public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	/// <summary>
	/// �������Ԃ��擾���܂��B
	/// </summary>
	float GetTimeLimit()
	{
		return m_timeLimit;
	}

private:
	Game* m_game = nullptr;

	FontRender m_timeLimitfontRender;	// �������Ԃ̃t�H���g��\�����邽�߂Ɏg�p���܂��B
	float m_timer = 0.0f;				// �o�ߎ��Ԃ��i�[����ϐ��ł��B
	float m_timeLimit = 0.0f;			// �c�莞�Ԃ��i�[����ϐ��ł��B
};