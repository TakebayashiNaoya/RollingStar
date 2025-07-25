/// <summary>
/// ゲームの進行を管理するクラス
/// </summary>
#pragma once
#include"Level3DRender/LevelRender.h"

class BackGround;
class GameCamera;
class GameTimer;
class LoadingView;
class Player;
class PopScoreManager;
class ResultView;
class Score;
class Star;
class StarSpawner;
class Transform;

class Game : public IGameObject
{
private:
	enum EnGameNewGOType
	{
		enGameNewGOType_Init,		// 何かしら初期化をします。１回だけ呼び出いものを最初に呼ぶ。
		enGameNewGOType_Step1,		// Playerなど数が多くないものをNewGOします。数が増えたら分割してください。
		EnGameNewGOType_Step2,		// StarなどLevelで大量に配置しているオブジェクトをNewGOします。ここで複数回分割を行います。
	};

public:
	Game();
	~Game();

	/// <summary>
	/// ゲーム開始フラグの状態を取得します。
	/// </summary>
	/// <returns>ゲームが開始されている場合は true、そうでない場合は false を返します。</returns>
	bool GetGameStartFlag()
	{
		return m_isGameStartFlag;
	}

	/// <summary>
	/// ゲーム開始フラグを設定します。
	/// </summary>
	/// <param name="a">設定するゲーム開始フラグの値（true または false）。</param>
	void SetGameStartFlag(bool a)
	{
		m_isGameStartFlag = a;
	}

	/// <summary>
	/// ゲーム終了フラグの状態を取得します。
	/// </summary>
	/// <returns>ゲームが終了している場合は true、そうでない場合は false を返します。</returns>
	bool GetGameEndFlag()
	{
		return  m_isGameEndFlag;
	}

	/// <summary>
	/// ゲーム終了フラグを設定します。
	/// </summary>
	/// <param name="a">設定するゲーム終了フラグの値（true または false）。</param>
	void SetGameEndFlag(bool a)
	{
		m_isGameEndFlag = a;
	}

private:
	bool Start()override final;
	void Update()override final;

	/// <summary>
	/// 空を初期化します。
	/// </summary>
	void InitSky();

	/// <summary>
	/// InitをUpdateに渡し、Updateで流れを調整することでロード画面を実装します。
	/// </summary>
	void InitLevelObjectDataList();

	/// <summary>
	/// レベルのオブジェクトを初期化します。
	/// </summary>
	void InitLevelObject(LevelObjectData& objData);

	BackGround* m_backGround = nullptr;						// ステージを描画するオブジェクト。
	GameCamera* m_gameCamera = nullptr;						// カメラを実装するオブジェクト。
	GameTimer* m_gameTimer = nullptr;						// インゲームの時間を管理し、描画するオブジェクト。
	LoadingView* m_loadingView = nullptr;					// ロード画面を描画するオブジェクト。
	Player* m_player = nullptr;								// プレイヤーを管理するオブジェクト。
	PopScoreManager* m_popScoreManager = nullptr;			// スター取得時にポップさせるスコアを管理するオブジェクト。
	ResultView* m_resultView = nullptr;						// リザルト画面を描画するオブジェクト。
	Score* m_score = nullptr;								// スコアを管理するオブジェクト。
	Transform* m_transform = nullptr;						// ステージとスターの親子付けを管理するオブジェクト。

	LevelRender m_levelRender;								// LevelRenderのインスタンス。
	std::vector<StarSpawner*>m_starSpawners;				// StarSpawnerクラスのポインタの配列を保持する変数（可変長配列）。
	std::vector<LevelObjectData> m_levelObjectDataList;		// LevelObjectDataクラスのインスタンスを複数格納するリスト。
	int m_objDataListIndex = 0;								// objDataのInit数を格納する変数。

	EnGameNewGOType m_gameNewGOType = enGameNewGOType_Init;	// NewGOを種類ごとに区切り、ロード画面の処理を差し込むために使用します。

	SkyCube* m_skyCube = nullptr;							// スカイキューブを描画するオブジェクト。
	int m_skyCubeType = enSkyCubeType_Night;				// スカイキューブの種類を設定します。
	Vector3 m_skyCubePos = Vector3::Zero;					// スカイキューブのポジションを設定します（基本的に原点）。

	bool m_isGameStartFlag = false;							// インゲームがスタートしたらtrueにして、各クラスの処理を始めます。
	bool m_isGameEndFlag = false;							// インゲームが終了したらtrueにして、各クラスの処理を止めます。
};