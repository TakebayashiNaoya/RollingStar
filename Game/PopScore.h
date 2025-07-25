/// <summary>
/// �X�R�A�|�b�v������@�\���Ǘ�����N���X
/// </summary>
#pragma once

class PopScoreManager;

class PopScore :public IGameObject
{
private:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	/// <summary>
	/// �t�F�[�h���ʂ̂���F�̌v�Z���s���܂��B
	/// </summary>
	void FadingColorCalc();

	struct PopScoreInfo
	{
		Vector2 popPosition = Vector2::Zero;
		float popScale = 0.0f;
		Vector4 popColor = { 0.0f,0.0f,0.0f,0.0f };
		int popPoint = 0;
	};


	PopScoreManager* m_popScoreManager = nullptr;

	FontRender m_popScoreFontRender;					// �|�b�v������X�R�A��`�悵�܂��B
	Vector4 m_setColor = { 0.0f,0.0f,0.0f,0.0f };		// �|�b�v������X�R�A�̐F���i�[���܂��B
	Vector4 m_fadingColor = { 0.0f,0.0f,0.0f,0.0f };	// �t�F�[�h���̐F���i�[���܂��B
	Vector2 m_fadePosition = Vector2::Zero;				// �|�b�v������X�R�A�̈ʒu���i�[���܂��B
	int m_setPoint = 0;									// �|�b�v������X�R�A�|�C���g���i�[���܂��B
	float m_fadeTimer = 0.0f;							// �t�F�[�h���ʂ̌p�����Ԃ��i�[���܂��B
	float m_setScale = 0.0f;							// �|�b�v������X�R�A�̃T�C�Y���i�[���܂��B


};

