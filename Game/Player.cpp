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
	//アニメーションクリップをロードする。
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);

	//ユニティちゃんのモデルを読み込む。
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);

	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/jump.wav");//ジャンプの音

	m_game = FindGO<Game>("game");

	return true;
}

//更新処理。
void Player::Update()
{
	Move();					//移動処理。
	Rotation();				//回転処理。
	ManageState();			//ステート管理。
	PlayAnimation();		//アニメーションの再生。
	m_modelRender.Update();	//絵描きさんの更新処理。
}

//描画処理。
void Player::Render(RenderContext& rc)
{
	//ユニティちゃんを描画する。
	m_modelRender.Draw(rc);
}


///////////////////////////////////////////////////////////////////
// ここからメソッドまとめ。
///////////////////////////////////////////////////////////////////


void Player::Move()
{
	if (m_game->m_gameStartFlag == true) {

		//xzの移動速度を0.0fにする。
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;

		//左スティックの入力量を取得。
		Vector3 stickL;
		stickL.x = g_pad[0]->GetLStickXF();
		stickL.y = g_pad[0]->GetLStickYF();

		//カメラの前方向と右方向のベクトルを持ってくる。
		Vector3 forward = g_camera3D->GetForward();
		Vector3 right = g_camera3D->GetRight();
		//y方向には移動させない。
		forward.y = 0.0f;
		right.y = 0.0f;

		//左スティックの入力量と120.0fを乗算。
		right *= stickL.x * 1.0f;
		forward *= stickL.y * 1.0f;

		//移動速度にスティックの入力量を加算する。
		m_moveSpeed += right + forward;

		//地面に付いていたら。
		if (m_characterController.IsOnGround())
		{
			//重力を無くす。
			m_moveSpeed.y = 0.0f;
			//Aボタンが押されたら。
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				//ジャンプさせる。
				m_moveSpeed.y = 240.0f;

				if (m_game->m_gameEndFlag == false) {
					//ジャンプの音を鳴らす。
					SoundSource* se = NewGO<SoundSource>(0);
					se->Init(3);
					se->Play(false);	//効果音はループさせないので、falseにする。
					se->SetVolume(3.5f);//音量を上げる。
				}
			}
		}
		//地面に付いていなかったら。
		else
		{
			//重力を発生させる。
			m_moveSpeed.y -= 2.5f;
		}

		//キャラクターコントローラーを使って座標を移動させる。
		m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
	}
	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);
}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}

//ステート管理。
void Player::ManageState()
{
	//地面に付いていなかったら。
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを1(ジャンプ中)にする。
		m_playerState = 1;
		//ここでManageStateの処理を終わらせる。
		return;
	}

	//地面に付いていたら。
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//ステートを2(歩き)にする。
		m_playerState = 2;
	}
	//xとzの移動速度が無かったら(スティックの入力が無かったら)。
	else
	{
		//ステートを0(待機)にする。
		m_playerState = 0;
	}
}

//アニメーションの再生。
void Player::PlayAnimation()
{
	//switch文。
	switch (m_playerState) {
		//プレイヤーステートが0(待機)だったら。
	case 0:
		//待機アニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
		//プレイヤーステートが1(ジャンプ中)だったら。
	case 1:
		//ジャンプアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
		//プレイヤーステートが2(歩き)だったら。
	case 2:
		//歩きアニメーションを再生する。
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}

