#include "stdafx.h"
#include "Player.h"
#include "SoundManager.h"
#include "Game.h"

namespace
{
	const char* ANIMATION_FILE_PATH = "Assets/animData/";

	/// <summary>
	/// アニメーションファイルのオプションを管理する構造体です。
	/// </summary>
	struct AnimationOption
	{
		const char* fileName;	// ファイルパス。
		bool is_loop = false;	// リピートするかどうか。（true=する、false=しない）

		std::string GetFullPath() const
		{
			return std::string(ANIMATION_FILE_PATH) + fileName;
		}
	};

	/// <summary>
	/// アニメーションのオプションを定義する定数配列です。
	/// </summary>
	const AnimationOption MODEL_LIST[] =
	{
		{"idle.tka",true},
		{"walk.tka",true},
		{"jump.tka",false}
	};

	const float CAPSULE_COLLIDET_RADIUS = 25.0f;	// カプセルコライダーの半径です。
	const float CAPSULE_COLLIDET_HEIGHT = 75.0f;	// カプセルコライダーの高さです。

	const float FIX_ZERO = 0.0f;					// 0.0fで固定するための定数です。
	const float FIX_ONE = 1.0f;						// プレイヤーは動かさず入力のみ得たいため。
	const float STICK_INPUT_JUDGE = 0.001f;			// スティックの入力を判定する数値です。
	const float RESET_ZERO = 0.0f;					// 0.0fで初期化するための定数です。
	const float GRAVITY = 2.5f;						// 重力の強さを設定します。
	const float JUMP_SPEED = 240.0f;				// ジャンプの上昇スピードを設定します。
}

bool Player::Start()
{
	SetAnimationClips();

	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	m_characterController.Init(CAPSULE_COLLIDET_RADIUS, CAPSULE_COLLIDET_HEIGHT, m_position);

	m_game = FindGO<Game>("game");


	return true;
}

void Player::Update()
{
	Move();
	Rotation();

	ManageState();
	m_modelRender.PlayAnimation(m_playerState);

	m_modelRender.Update();
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void Player::SetAnimationClips()
{
	for (int animKinds = 0; animKinds < enAnimationClip_Num; animKinds++)
	{
		m_animationClips[animKinds].Load(MODEL_LIST[animKinds].GetFullPath().c_str());
		m_animationClips[animKinds].SetLoopFlag(MODEL_LIST[animKinds].is_loop);
	}
}

void Player::Move()
{
	if (m_game->GetGameStartFlag())
	{
		// xzの移動速度を0.0fにします。
		m_moveSpeed.x = RESET_ZERO;
		m_moveSpeed.z = RESET_ZERO;

		// 左スティックの入力量を取得します。
		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		// カメラの前方向と右方向のベクトルを持ってきます。
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();

		forward.y = FIX_ZERO;
		right.y = FIX_ZERO;

		right *= stickL.x * FIX_ONE;
		forward *= stickL.y * FIX_ONE;

		// 移動速度にスティックの入力量を加算します。
		m_moveSpeed += right + forward;

		if (m_characterController.IsOnGround())
		{
			m_moveSpeed.y = RESET_ZERO;

			if (g_pad[0]->IsTrigger(enButtonA))
			{
				// ジャンプ。
				m_moveSpeed.y = JUMP_SPEED;

				SoundManager* soundManager = FindGO<SoundManager>("soundmanager");
				soundManager->SoundNewGO(enSoundList_JumpSE);
			}
		}
		else
		{
			// 重力。
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
	if (!m_characterController.IsOnGround())
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