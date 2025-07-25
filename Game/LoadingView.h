/// <summary>
/// ���[�h��ʂ��Ǘ�����N���X
/// </summary>
#pragma once

class LoadingView :public IGameObject
{
public:
	/// <summary>
	/// ���[�h�t�F�[�Y��\���񋓌^�ł��B
	/// </summary>
	enum EnLoadingPhase
	{
		enLoadingPhase_First,	// ���[�h�̐i��1/6�������B
		enLoadingPhase_Second,	// ���[�h�̐i��2/6�������B
		enLoadingPhase_Third,	// ���[�h�̐i��3/6�������B
		enLoadingPhase_Fourth,	// ���[�h�̐i��4/6�������B
		enLoadingPhase_Fifth,	// ���[�h�̐i��5/6�������B
		enLoadingPhase_Sixth,	// ���[�h�̐i��6/6�������B
		Phase_Num
	};

	bool showLoadingPhases[Phase_Num] = { false };	// ���̔z��Ń��[�h�̐i���������X�^�[�̏������ƈʒu�ݒ���s���܂��B

	~LoadingView();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	SpriteRender m_LoadingSceneSpriteRender;				// ���[�h��ʂ̔w�i��\�����܂��B
	FontRender m_pushA_FontRender;							// �uPUSH(A)�v�ƕ\�����܂��B
	SpriteRender m_LoadingPhaseSpriteRenders[Phase_Num];	// ���[�h�̐i���ɍ��킹�ăX�^�[��\�����܂��B
};

