///
/// �J�����ƂȂ�N���X
///
#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	bool Start()override;
	void Update()override;

private:
	Player* m_player = nullptr;

private:
	Vector3 m_toCameraPos = Vector3::Zero;	//�����_���王�_�Ɍ������x�N�g��
};