#include "stdafx.h"
#include "BackGround.h"
#include"Transform.h"
#include"Game.h"

class Transform;
//test
namespace
{
	/**
	 * �����͒萔�������ӏ�
	 * �萔�̕ϐ��������Ƃ��̒��ӓ_
	 *		�^���̑O�Ɂuconst�v������@��Fconst �^�� �ϐ��� = 1.0f;
	 *		�P���؂�ŃA���_�[�o�[������
	 *		�S���啶��
	 *		�ڂ����̓Q�[���v���O���~���O���ނ�extra�ɏ����Ă�̂Ń`�F�b�N�I�I
	 */
	const float SPEED_POWER = 0.5f;	//��]�X�s�[�h
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

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF(); //���E����
	stickL.y = g_pad[0]->GetLStickYF(); //�O�����

	//�J�����̑O�����ƉE�����̃x�N�g�����擾�B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//�ړ�������Y�������[���ɂ��Ēn�ʕ��ʏ�ɐ����B
	forward.y = 0.0f;
	right.y = 0.0f;

	//���K�����ĕ����x�N�g���ɕϊ�
	forward.Normalize();
	right.Normalize();

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed = right * stickL.x + forward * stickL.y;

	if (m_moveSpeed.Length() > 0.01f)
	{
		//�p�b�h���͂�����ΐ��K�����ĕ����݂̂��擾�B
		//���R�F�����̏��͉�]�ʂɂ͎g��Ȃ�����B
		m_moveSpeed.Normalize();

		// �X�e�B�b�N�����ɉ�������]���쐬�B
		// X���i���E�����j��Z�����̃X�e�B�b�N���́i�O��j
		Vector3 axisX = Vector3::AxisX;
		float angleX = -m_moveSpeed.z * SPEED_POWER;

		// Z���i�O������j��X�����̃X�e�B�b�N���́i���E�j
		Vector3 axisZ = Vector3::AxisZ;
		float angleZ = m_moveSpeed.x * SPEED_POWER;

		// �e�����Ƃ�Quaternion���쐬
		Quaternion rotX, rotZ;
		rotX.SetRotationDeg(axisX, angleX);
		rotZ.SetRotationDeg(axisZ, angleZ);

		// ������]�i���ԁFZ �� X�A�K�v�Ȃ�t���j
		Quaternion deltaRotation = rotZ * rotX;

		// ���݂̉�]�ɍ���
		m_rotationQuat = deltaRotation * m_rotationQuat;
		m_transform->m_localRotation = m_rotationQuat;
	}

	//�G�`������ɉ�]��������B
	m_modelRender.SetRotation(m_rotationQuat);
}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}