/// <summary>
/// プレイヤーとなるクラス
/// </summary>
#pragma once

class Game;

class Player : public IGameObject
{
private:
	/// <summary>
	/// アニメーションのクリップタイプを表す列挙型です。
	/// </summary>
	enum EnAnimationClip
	{
		enAnimationClip_Idle,	// 待機アニメーション。
		enAnimationClip_Walk,	// 移動アニメーション。
		enAnimationClip_Jump,	// ジャンプアニメーション。
		enAnimationClip_Num,
	};

public:
	/// <summary>
	/// 現在の位置ベクトルを取得します。
	/// </summary>
	/// <returns>現在の位置を表す Vector3 型の値。</returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move();

	/// <summary>
	/// 回転処理。
	/// </summary>
	void Rotation();

	/// <summary>
	/// 状態を管理するための関数です。
	/// </summary>
	void ManageState();

	/// <summary>
	/// アニメーションを再生します。
	/// </summary>
	void PlayAnimation();

	Game* m_game = nullptr;

	Vector3 m_position = { 0.0f,3000.0f,0.0f };				// 月の半径が3000のため。
	Quaternion m_rotation;									// プレイヤーの回転を格納します。
	ModelRender m_modelRender;								// プレイヤーを描画します。
	AnimationClip m_animationClips[enAnimationClip_Num];	// アニメーションを管理します。
	CharacterController m_characterController;				// プレイヤーの当たり判定を管理します。
	Vector3 m_moveSpeed = Vector3::Zero;					// プレイヤーの移動方向を格納します。
	int m_playerState = 0;									// プレイヤーの状態（Idle,Walk,Jump）を格納します。
};
