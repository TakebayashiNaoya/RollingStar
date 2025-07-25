/// <summary>
/// �X�^�[���Ǘ�����N���X
/// </summary>
#pragma once

class Game;
class Player;
class PopScoreManager;
class Score;
class Transform;

class Star :public IGameObject
{
public:
	/// <summary>
	/// �I�u�W�F�N�g�����ł��Ă��邩�𔻒肵�܂��B
	/// </summary>
	/// <returns>���ł��Ă���ꍇ�� true�A�����łȂ��ꍇ�� false ��Ԃ��܂��B</returns>
	bool GetIsDead()
	{
		return m_isDead;
	}

	/// <summary>
	/// Transform �I�u�W�F�N�g��ݒ肵�܂��B
	/// </summary>
	/// <param name="p">�ݒ肷�� Transform �I�u�W�F�N�g�ւ̃|�C���^�B</param>
	void SetTransform(Transform* p)
	{
		m_transform = p;
	}

private:
	bool Start() override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// �X�^�[�̐F��ݒ肵�܂��B
	/// </summary>
	void SetStarColor();

	/// <summary>
	/// �X�^�[�̐F�ɍ��킹�ă��f�������_�[���������B
	/// </summary>
	void StarModelInit();

	/// <summary>
	/// �X�^�[���擾���鏈���B
	/// </summary>
	void GetStar();

	/// <summary>
	/// �X�^�[�̎��]�����B
	/// </summary>
	void Rotation();

	Game* m_game = nullptr;
	Player* m_player = nullptr;
	PopScoreManager* m_popScoreManager = nullptr;
	Score* m_score = nullptr;
	Transform* m_transform = nullptr;

	ModelRender m_modelRender;				// �X�^�[��`��B
	Quaternion m_rotation;					// �X�^�[�̎��]�p�x���i�[�B
	int m_starColor;						// �X�^�[�̐F���i�[����B
	bool m_isDead = false;					// �X�^�[��Delete���ꂽ�Ƃ��Atrue�ɂ���StarSpawner�N���X�ɓ`����B
};