#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "sound/SoundEngine.h"2
#include "sound/SoundSource.h"

Player::~Player()
{

}

bool Player::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	//���j�e�B�����̃��f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);

	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/jump.wav");//�W�����v�̉�

	m_game = FindGO<Game>("game");

	return true;
}

//�X�V�����B
void Player::Update()
{
	Move();					//�ړ������B
	Rotation();				//��]�����B
	ManageState();			//�X�e�[�g�Ǘ��B
	PlayAnimation();		//�A�j���[�V�����̍Đ��B
	m_modelRender.Update();	//�G�`������̍X�V�����B
}

//�`�揈���B
void Player::Render(RenderContext& rc)
{
	//���j�e�B������`�悷��B
	m_modelRender.Draw(rc);
}


///////////////////////////////////////////////////////////////////
// �������烁�\�b�h�܂Ƃ߁B
///////////////////////////////////////////////////////////////////


void Player::Move()
{
	if (m_game->m_gameStartFlag == true) {

		//xz�̈ړ����x��0.0f�ɂ���B
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		//���X�e�B�b�N�̓��͗ʂ��擾�B
		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();
		//y�����ɂ͈ړ������Ȃ��B
		forward.y = 0.0f;
		right.y = 0.0f;

		//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
		right *= stickL.x * 1.0f;
		forward *= stickL.y * 1.0f;

		//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
		m_moveSpeed += right + forward;

		//�n�ʂɕt���Ă�����B
		if (m_characterController.IsOnGround())
		{
			//�d�͂𖳂����B
			m_moveSpeed.y = 0.0f;
			//A�{�^���������ꂽ��B
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//�W�����v������B
				m_moveSpeed.y = 240.0f;

				if (m_game->m_gameEndFlag == false) {
					//�W�����v�̉���炷�B
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(3);
					se->Play(false);	//���ʉ��̓��[�v�����Ȃ��̂ŁAfalse�ɂ���B
					se->SetVolume(3.5f);//���ʂ��グ��B
				}
			}
		}
		//�n�ʂɕt���Ă��Ȃ�������B
		else
		{
			//�d�͂𔭐�������B
			m_moveSpeed.y -= 2.5f;
		}

		//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
		m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	}
	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

//�X�e�[�g�Ǘ��B
void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������B
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g��1(�W�����v��)�ɂ���B
		m_playerState = 1;
		//������ManageState�̏������I��点��B
		return;
	}

	//�n�ʂɕt���Ă�����B
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�X�e�[�g��2(����)�ɂ���B
		m_playerState = 2;
	}
	//x��z�̈ړ����x������������(�X�e�B�b�N�̓��͂�����������)�B
	else
	{
		//�X�e�[�g��0(�ҋ@)�ɂ���B
		m_playerState = 0;
	}
}

//�A�j���[�V�����̍Đ��B
void Player::PlayAnimation()
{
	//switch���B
	switch (m_playerState) {
		//�v���C���[�X�e�[�g��0(�ҋ@)��������B
	case 0:
		//�ҋ@�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//�v���C���[�X�e�[�g��1(�W�����v��)��������B
	case 1:
		//�W�����v�A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//�v���C���[�X�e�[�g��2(����)��������B
	case 2:
		//�����A�j���[�V�������Đ�����B
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}

