/// <summary>
/// �`���[�g���A�����Ǘ�����N���X
/// </summary>
#pragma once

class CountDown;
class Game;
class GameTimer;

class Tutorial :public IGameObject
{
public:
	~Tutorial();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	SpriteRender m_spriteRender;	// �`���[�g���A����ʂ�\������B
	bool m_countDownFlag = false;	// �J�E���g�_�E�����J�n����t���O�B
};

