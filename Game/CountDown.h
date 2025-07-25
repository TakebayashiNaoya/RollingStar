/// <summary>
/// �Q�[���X�^�[�g���̃J�E���g�_�E���N���X
/// </summary>
#pragma once
class Game;

class CountDown :public IGameObject
{
public:
	CountDown();
	~CountDown();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// �X�v���C�g�����_�[���v�Z���ĕԂ��܂��B
	/// </summary>
	/// <returns>�v�Z���ꂽ SpriteRender �I�u�W�F�N�g�ւ̃|�C���^�B</returns>
	SpriteRender* ComputeSpriteRender();

	Game* m_game = nullptr;					// Game�^�̃|�C���^�B
	SpriteRender* m_spriteRender = nullptr;	// SpriteRender�^�̃|�C���^�B

	SpriteRender m_countThreeSpriteRender;		//�u3�v�ƕ\�����邽�߂�SpriteRender�C���X�^���X�B
	SpriteRender m_countTwoSpriteRender;		//�u2�v�ƕ\�����邽�߂�SpriteRender�C���X�^���X�B
	SpriteRender m_countOneSpriteRender;		//�u1�v�ƕ\�����邽�߂�SpriteRender�C���X�^���X�B
	SpriteRender m_countStartSpriteRender;	//�uSTART�v�ƕ\�����邽�߂�SpriteRender�C���X�^���X�B

	float countDown = 0.0f;					// SpriteRender��؂�ւ��鎞�Ԃ��v�����邽�߂̕ϐ��B
};

