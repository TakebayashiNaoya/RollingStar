/// <summary>
/// �n�ʂƂȂ�N���X
/// </summary>
#pragma once

class Game;
class Transform;

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();

	/// <summary>
	/// m_transform �����o�[�ւ̃|�C���^���擾���܂��B
	/// </summary>
	/// <returns>Transform �^�̃|�C���^�Bm_transform �����o�[�ւ̃|�C���^��Ԃ��܂��B</returns>
	Transform* GetTransform()
	{
		return m_transform;
	}

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// ��]��������s���܂��B
	/// </summary>
	void Rotation();

	Game* m_game = nullptr;
	Transform* m_transform = nullptr;

	ModelRender	m_modelRender;							// ���f���̕`����Ǘ����� ModelRender �^�̃I�u�W�F�N�g�B
	PhysicsStaticObject m_physicsStaticObject;			// �����蔻��̎����B
	Quaternion m_rotationQuat = Quaternion::Identity;	// ������]��P��Quaternion�i����]�j�ŏ������B
	Vector3	m_rotationVector = Vector3::Zero;			// ��]�x�N�g�����������B
};