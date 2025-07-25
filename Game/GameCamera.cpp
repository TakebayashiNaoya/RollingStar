#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace
{
	const float ROT_SPEED = 1.3f;			// カメラの回転速度を設定します。
	const float CAMERA_VECTOR_MAX = 0.9f;	// カメラ回転の上限を設定します。
	const float CAMERA_VECTOR_MIN = -0.2f;	// カメラ回転の下限を設定します。
}

bool GameCamera::Start()
{
	// 注視点から視点までのベクトルを設定します。
	m_toCameraPos.Set(0.0f, 600.0f, -700.0f);

	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	return true;
}
void GameCamera::Update()
{
	// 注視点を計算します。
	Vector3 target = m_player->GetPosition();

	// プレイヤの足元からちょっと上を注視点とします。
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	// Y軸周りの回転。
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, ROT_SPEED * x);
	qRot.Apply(m_toCameraPos);

	// X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, ROT_SPEED * y);
	qRot.Apply(m_toCameraPos);

	// カメラの回転の上限をチェックします。
	// 注視点から視点までのベクトルを正規化します。
	// 正規化すると、ベクトルの大きさが１になります。
	// 大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となります。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < CAMERA_VECTOR_MIN)
	{
		// カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > CAMERA_VECTOR_MAX)
	{
		// カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	// 視点を計算します。
	Vector3 pos = target + m_toCameraPos;

	// メインカメラに注視点と視点を設定します。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	g_camera3D->Update();
}