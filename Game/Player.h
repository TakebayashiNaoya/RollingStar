#pragma once
class Game;

//プレイヤークラス。
class Player : public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();					//更新処理。
	void Render(RenderContext& rc);	//描画処理。
	void Move();					//移動処理。
	void Rotation();				//回転処理。
	void ManageState();				//ステート管理。
	void PlayAnimation();			//アニメーションの再生。

	//メンバ変数。
	ModelRender m_modelRender;	//モデルレンダ―。
	Vector3 m_position;			//座標。
	enum EnAnimationClip {		//アニメーション。
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	Game* m_game;
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ。
	CharacterController m_characterController;			//キャラクターコントローラー。
	Vector3 m_moveSpeed;								//移動速度。
	Quaternion m_rotation;								//クォータニオン。
	int m_playerState = 0;								//プレイヤーのステート(状態)を表す変数。
	int m_starCount = 0;								//集めた☆の数をカウントする。
};
