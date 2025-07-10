///
/// プレイヤーとなるクラス
///
#pragma once

class Game;

class Player : public IGameObject
{
private:
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

public:
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

public:
	Vector3 GetPosition()
	{
		return m_position;
	}

private:
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();

private:
	Game* m_game = nullptr;

private:
	Vector3 m_position = { 0.0f,3000.0f,0.0f };//月の半径が3000のため
	Quaternion m_rotation;
	Vector3 m_scale = Vector3::Zero;
	ModelRender m_modelRender;
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Vector3 m_moveSpeed = Vector3::Zero;
	int m_playerState = 0;
	int m_starCount = 0;
};
