#pragma once
class Game;

//�v���C���[�N���X�B
class Player : public IGameObject
{
public:
	~Player();
	bool Start();
	void Update();					//�X�V�����B
	void Render(RenderContext& rc);	//�`�揈���B
	void Move();					//�ړ������B
	void Rotation();				//��]�����B
	void ManageState();				//�X�e�[�g�Ǘ��B
	void PlayAnimation();			//�A�j���[�V�����̍Đ��B

	//�����o�ϐ��B
	ModelRender m_modelRender;	//���f�������_�\�B
	enum EnAnimationClip {		//�A�j���[�V�����B
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

	Vector3 m_position = { 0.0f,3000.0f,0.0f };
	Quaternion m_rotation;
	Vector3 m_scale;
	Game* m_game;
	AnimationClip m_animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v�B
	CharacterController m_characterController;			//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;								//�ړ����x�B
	int m_playerState = 0;								//�v���C���[�̃X�e�[�g(���)��\���ϐ��B
	int m_starCount = 0;								//�W�߂����̐����J�E���g����B
};
