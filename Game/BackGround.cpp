#include "stdafx.h"
#include "BackGround.h"
#include"Game.h"
#include"Transform.h"

namespace
{
	const float SPEED_POWER = 0.4f;			// ��]�X�s�[�h��ݒ肵�܂��B
	const float STICK_INPUT_JUDGE = 0.01f;	// �X�e�B�b�N�̓��͂����邩�𓾂����l�ł��B
	const float FIX_ZERO = 0.0f;			// 0.0f�ŏ��������邽�߂̒萔�ł��B
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

	//�ړ�������Y�������[���ɂ��Ēn�ʕ��ʏ�ɐ������܂��B
	forward.y = FIX_ZERO;
	right.y = FIX_ZERO;

	forward.Normalize();
	right.Normalize();

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z���܂��B
	m_rotationVector = right * stickL.x + forward * stickL.y;

	if (m_rotationVector.Length() > STICK_INPUT_JUDGE)
	{
		//�p�b�h���͂�����ΐ��K�����ĕ����݂̂��擾���܂��B
		//���R�F�����̏��͉�]�ʂɂ͎g��Ȃ����߁B
		m_rotationVector.Normalize();

		// �X�e�B�b�N�����ɉ�������]���쐬���܂��B
		// X���i���E�����j��Z�����̃X�e�B�b�N���́i�O��j�B
		Vector3 axisX = Vector3::AxisX;
		float angleX = -m_rotationVector.z * SPEED_POWER;

		// Z���i�O������j��X�����̃X�e�B�b�N���́i���E�j�B
		Vector3 axisZ = Vector3::AxisZ;
		float angleZ = m_rotationVector.x * SPEED_POWER;

		Quaternion rotX, rotZ;
		rotX.SetRotationDeg(axisX, angleX);
		rotZ.SetRotationDeg(axisZ, angleZ);

		// ������]�i���ԁFZ �� X�A�K�v�Ȃ�t���j�B
		Quaternion deltaRotation = rotZ * rotX;

		// ���݂̉�]�ɍ������܂��B
		m_rotationQuat = deltaRotation * m_rotationQuat;
		m_transform->m_localRotation = m_rotationQuat;
	}

	m_modelRender.SetRotation(m_rotationQuat);
}