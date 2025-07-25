#include "stdafx.h"
#include "Player.h"
#include "SoundManager.h"
#include "Game.h"

namespace
{
	const float FIX_ZERO = 0.0f;			// 0.0f�ŌŒ肷�邽�߂̒萔�ł��B
	const float FIX_ONE = 1.0f;				// �v���C���[�͓����������͂̂ݓ��������߁B
	const float STICK_INPUT_JUDGE = 0.001f;	// �X�e�B�b�N�̓��͂𔻒肷�鐔�l�ł��B
	const float RESET_ZERO = 0.0f;			// 0.0f�ŏ��������邽�߂̒萔�ł��B
	const float GRAVITY = 2.5f;				// �d�͂̋�����ݒ肵�܂��B
	const float JUMP_SPEED = 240.0f;		// �W�����v�̏㏸�X�s�[�h��ݒ肵�܂��B
}

bool Player::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	m_characterController.Init(25.0f, 75.0f, m_position);

	m_game = FindGO<Game>("game");


	return true;
}

void Player::Update()
{
	Move();
	Rotation();
	ManageState();
	PlayAnimation();
	m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Player::Move()
{
	if (m_game->GetGameStartFlag())
	{
		// xz�̈ړ����x��0.0f�ɂ��܂��B
		m_moveSpeed.x = RESET_ZERO;
		m_moveSpeed.z = RESET_ZERO;

		// ���X�e�B�b�N�̓��͗ʂ��擾���܂��B
		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		// �J�����̑O�����ƉE�����̃x�N�g���������Ă��܂��B
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

		forward.y = FIX_ZERO;
		right.y = FIX_ZERO;

		right *= stickL.x * FIX_ONE;
		forward *= stickL.y * FIX_ONE;

		// �ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z���܂��B
		m_moveSpeed += right + forward;

		if (m_characterController.IsOnGround())
		{
			m_moveSpeed.y = RESET_ZERO;

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				// �W�����v�B
				m_moveSpeed.y = JUMP_SPEED;

				SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
				soundManager->SoundNewGO(enSoundList_JumpSE);
			}
		}
		else
		{
			// �d�́B
			m_moveSpeed.y -= GRAVITY;
		}

		m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	}

	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= STICK_INPUT_JUDGE || fabsf(m_moveSpeed.z) >= STICK_INPUT_JUDGE)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	if (m_characterController.IsOnGround() == false)
	{
		m_playerState = enAnimationClip_Jump;
		return;
	}

	if (fabsf(m_moveSpeed.x) >= STICK_INPUT_JUDGE || fabsf(m_moveSpeed.z) >= STICK_INPUT_JUDGE)
	{
		m_playerState = enAnimationClip_Walk;
	}
	else
	{
		m_playerState = enAnimationClip_Idle;
	}
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case enAnimationClip_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case enAnimationClip_Walk:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case enAnimationClip_Jump:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	}
}

