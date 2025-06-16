#include "stdafx.h"
#include "BackGround.h"
#include"Transform.h"
#include"Game.h"

class Transform;
//test
namespace
{
	/**
	 * ここは定数を書く箇所
	 * 定数の変数を書くときの注意点
	 *		型名の前に「const」をつける　例：const 型名 変数名 = 1.0f;
	 *		単語区切りでアンダーバーをつける
	 *		全部大文字
	 *		詳しくはゲームプログラミング教材のextraに書いてるのでチェック！！
	 */
	const float SPEED_POWER = 0.5f;	//回転スピード
}

BackGround::BackGround()
{
	m_transform = new Transform;
	m_modelRender.Init("Assets/modelData/moon.tkm");
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{
	delete m_transform;
}

bool BackGround::Start()
{
	m_game = FindGO<Game>("game");
	return true;
}

void BackGround::Update()
{
	Rotation();

	m_transform->UpdateTransform();

	m_modelRender.Update();
}

void BackGround::Rotation()
{
	if (m_game->m_gameStartFlag == false) {
		return;
	}

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF(); //左右方向
	stickL.y = g_pad[0]->GetLStickYF(); //前後方向

	//カメラの前方向と右方向のベクトルを取得。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//移動方向のY成分をゼロにして地面平面上に制限。
	forward.y = 0.0f;
	right.y = 0.0f;

	//正規化して方向ベクトルに変換
	forward.Normalize();
	right.Normalize();

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed = right * stickL.x + forward * stickL.y;

	if (m_moveSpeed.Length() > 0.01f)
	{
		//パッド入力があれば正規化して方向のみを取得。
		//理由：長さの情報は回転量には使わないから。
		m_moveSpeed.Normalize();

		// スティック方向に応じた回転を作成。
		// X軸（左右方向）にZ方向のスティック入力（前後）
		Vector3 axisX = Vector3::AxisX;
		float angleX = -m_moveSpeed.z * SPEED_POWER;

		// Z軸（前後方向）にX方向のスティック入力（左右）
		Vector3 axisZ = Vector3::AxisZ;
		float angleZ = m_moveSpeed.x * SPEED_POWER;

		// 各軸ごとにQuaternionを作成
		Quaternion rotX, rotZ;
		rotX.SetRotationDeg(axisX, angleX);
		rotZ.SetRotationDeg(axisZ, angleZ);

		// 合成回転（順番：Z → X、必要なら逆も可）
		Quaternion deltaRotation = rotZ * rotX;

		// 現在の回転に合成
		m_rotationQuat = deltaRotation * m_rotationQuat;
		m_transform->m_localRotation = m_rotationQuat;
	}

	//絵描きさんに回転を教える。
	m_modelRender.SetRotation(m_rotationQuat);
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}