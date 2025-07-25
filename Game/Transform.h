/// <summary>
/// トランスフォームを管理するクラス
/// </summary>
#pragma once

class Transform : public Noncopyable
{
	//public関数
public:
	Transform();
	~Transform();

	//更新処理
	void UpdateTransform();
	//ワールド行列更新、UpdateTransformの方で呼ばれるので呼び出す必要なし
	void UpdateWorldMatrix();

	//全ての子トランスフォームとの紐づけを外す
	void Release();

	//特定の子トランスフォームとの紐づけを外す
	void RemoveChild(Transform* t);

	//親トランスフォームを設定
	void SetParent(Transform* p)
	{
		m_parent = p;
		m_parent->m_children.push_back(this);
	}

	//public変数
public:
	//自身のパラメータ
	Vector3 m_localPosition;
	Quaternion m_localRotation;
	Vector3 m_localScale;

	//親トランスフォームを考慮したパラメータ
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;

	//private変数
	//基本的に関数以外から弄る必要なし
private:

	Matrix m_rotationMatrix;
	Matrix m_worldMatrix;

	Transform* m_parent;
	std::vector<Transform*> m_children;

};
