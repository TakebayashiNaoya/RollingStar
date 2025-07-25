/// <summary>
/// �v���C���[�ƂȂ�N���X
/// </summary>
#pragma once

class Game;

class Player : public IGameObject
{
private:
	/// <summary>
	/// �A�j���[�V�����̃N���b�v�^�C�v��\���񋓌^�ł��B
	/// </summary>
	enum EnAnimationClip
	{
		enAnimationClip_Idle,	// �ҋ@�A�j���[�V�����B
		enAnimationClip_Walk,	// �ړ��A�j���[�V�����B
		enAnimationClip_Jump,	// �W�����v�A�j���[�V�����B
		enAnimationClip_Num,
	};

public:
	/// <summary>
	/// ���݂̈ʒu�x�N�g�����擾���܂��B
	/// </summary>
	/// <returns>���݂̈ʒu��\�� Vector3 �^�̒l�B</returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();

	/// <summary>
	/// ��]�����B
	/// </summary>
	void Rotation();

	/// <summary>
	/// ��Ԃ��Ǘ����邽�߂̊֐��ł��B
	/// </summary>
	void ManageState();

	/// <summary>
	/// �A�j���[�V�������Đ����܂��B
	/// </summary>
	void PlayAnimation();

	Game* m_game = nullptr;

	Vector3 m_position = { 0.0f,3000.0f,0.0f };				// ���̔��a��3000�̂��߁B
	Quaternion m_rotation;									// �v���C���[�̉�]���i�[���܂��B
	ModelRender m_modelRender;								// �v���C���[��`�悵�܂��B
	AnimationClip m_animationClips[enAnimationClip_Num];	// �A�j���[�V�������Ǘ����܂��B
	CharacterController m_characterController;				// �v���C���[�̓����蔻����Ǘ����܂��B
	Vector3 m_moveSpeed = Vector3::Zero;					// �v���C���[�̈ړ��������i�[���܂��B
	int m_playerState = 0;									// �v���C���[�̏�ԁiIdle,Walk,Jump�j���i�[���܂��B
};
