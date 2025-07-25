/// <summary>
/// スターを管理するクラス
/// </summary>
#pragma once

class Game;
class Player;
class PopScoreManager;
class Score;
class Transform;

class Star :public IGameObject
{
public:
	/// <summary>
	/// オブジェクトが消滅しているかを判定します。
	/// </summary>
	/// <returns>消滅している場合は true、そうでない場合は false を返します。</returns>
	bool GetIsDead()
	{
		return m_isDead;
	}

	/// <summary>
	/// Transform オブジェクトを設定します。
	/// </summary>
	/// <param name="p">設定する Transform オブジェクトへのポインタ。</param>
	void SetTransform(Transform* p)
	{
		m_transform = p;
	}

private:
	bool Start() override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	/// <summary>
	/// スターの色を設定します。
	/// </summary>
	void SetStarColor();

	/// <summary>
	/// スターの色に合わせてモデルレンダーを初期化。
	/// </summary>
	void StarModelInit();

	/// <summary>
	/// スターを取得する処理。
	/// </summary>
	void GetStar();

	/// <summary>
	/// スターの自転処理。
	/// </summary>
	void Rotation();

	Game* m_game = nullptr;
	Player* m_player = nullptr;
	PopScoreManager* m_popScoreManager = nullptr;
	Score* m_score = nullptr;
	Transform* m_transform = nullptr;

	ModelRender m_modelRender;				// スターを描画。
	Quaternion m_rotation;					// スターの自転角度を格納。
	int m_starColor;						// スターの色を格納する。
	bool m_isDead = false;					// スターがDeleteされたとき、trueにしてStarSpawnerクラスに伝える。
};