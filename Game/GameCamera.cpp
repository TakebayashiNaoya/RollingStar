#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace
{
	const float ROT_SPEED = 1.3f;			// �J�����̉�]���x��ݒ肵�܂��B
	const float CAMERA_VECTOR_MAX = 0.9f;	// �J������]�̏����ݒ肵�܂��B
	const float CAMERA_VECTOR_MIN = -0.2f;	// �J������]�̉�����ݒ肵�܂��B
}

bool GameCamera::Start()
{
	// �����_���王�_�܂ł̃x�N�g����ݒ肵�܂��B
	m_toCameraPos.Set(0.0f, 600.0f, -700.0f);

	m_player = FindGO<Player>("player");

	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(5000.0f);

	return true;
}
void GameCamera::Update()
{
	// �����_���v�Z���܂��B
	Vector3 target = m_player->GetPosition();

	// �v���C���̑������炿����Ə�𒍎��_�Ƃ��܂��B
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();

	// Y������̉�]�B
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, ROT_SPEED * x);
	qRot.Apply(m_toCameraPos);

	// X������̉�]�B
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, ROT_SPEED * y);
	qRot.Apply(m_toCameraPos);

	// �J�����̉�]�̏�����`�F�b�N���܂��B
	// �����_���王�_�܂ł̃x�N�g���𐳋K�����܂��B
	// ���K������ƁA�x�N�g���̑傫�����P�ɂȂ�܂��B
	// �傫�����P�ɂȂ�Ƃ������Ƃ́A�x�N�g�����狭�����Ȃ��Ȃ�A�����݂̂̏��ƂȂ�܂��B
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < CAMERA_VECTOR_MIN)
	{
		// �J����������������B
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > CAMERA_VECTOR_MAX)
	{
		// �J�����������������B
		m_toCameraPos = toCameraPosOld;
	}

	// ���_���v�Z���܂��B
	Vector3 pos = target + m_toCameraPos;

	// ���C���J�����ɒ����_�Ǝ��_��ݒ肵�܂��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	g_camera3D->Update();
}