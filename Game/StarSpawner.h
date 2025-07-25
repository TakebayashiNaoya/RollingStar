/// <summary>
/// �X�^�[�X�|�i�[���Ǘ�����N���X
/// </summary>
#pragma once

class BackGround;
class Star;
class Transform;

class StarSpawner :public IGameObject
{
public:
	StarSpawner();
	~StarSpawner();

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

	BackGround* m_backGround = nullptr;
	Star* m_star = nullptr;
	Transform* m_transform = nullptr;

	float m_respawnTimer = 0.0f;	// �X�^�[�̃��X�|�[�����Ԃ��i�[����B
};
