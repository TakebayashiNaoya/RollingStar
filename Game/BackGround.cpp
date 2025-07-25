#include "stdafx.h"
#include "BackGround.h"
#include"Game.h"
#include"Transform.h"

namespace
{
	const float SPEED_POWER = 0.4f;			// 回転スピードを設定します。
	const float STICK_INPUT_JUDGE = 0.01f;	// スティックの入力があるかを得る基準数値です。
	const float FIX_ZERO = 0.0f;			// 0.0fで初期化するための定数です。
}

BackGround::BackGround()
{
	m_transform = new Transform;
}

BackGround::~BackGround()
{
	delete m_transform;
}

bool BackGround::Start()
{
	m_modelRender.Init("Assets/modelData/moon.tkm");
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_game = FindGO<Game>("game");
	return true;
}

void BackGround::Update()
{
	Rotation();

	m_transform->UpdateTransform();

	m_modelRender.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

void BackGround::Rotation()
{
	if (m_game->GetGameStartFlag() == false)
	{
		return;
	}

	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//移動方向のY成分をゼロにして地面平面上に制限します。
	forward.y = FIX_ZERO;
	right.y = FIX_ZERO;

	forward.Normalize();
	right.Normalize();

	//移動速度にスティックの入力量を加算します。
	m_rotationVector = right * stickL.x + forward * stickL.y;

	if (m_rotationVector.Length() > STICK_INPUT_JUDGE)
	{
		//パッド入力があれば正規化して方向のみを取得します。
		//理由：長さの情報は回転量には使わないため。
		m_rotationVector.Normalize();

		// スティック方向に応じた回転を作成します。
		// X軸（左右方向）にZ方向のスティック入力（前後）。
		Vector3 axisX = Vector3::AxisX;
		float angleX = -m_rotationVector.z * SPEED_POWER;

		// Z軸（前後方向）にX方向のスティック入力（左右）。
		Vector3 axisZ = Vector3::AxisZ;
		float angleZ = m_rotationVector.x * SPEED_POWER;

		Quaternion rotX, rotZ;
		rotX.SetRotationDeg(axisX, angleX);
		rotZ.SetRotationDeg(axisZ, angleZ);

		// 合成回転（順番：Z → X、必要なら逆も可）。
		Quaternion deltaRotation = rotZ * rotX;

		// 現在の回転に合成します。
		m_rotationQuat = deltaRotation * m_rotationQuat;
		m_transform->m_localRotation = m_rotationQuat;
	}

	m_modelRender.SetRotation(m_rotationQuat);
}