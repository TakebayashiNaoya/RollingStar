/// <summary>
/// �^�C�g�����Ǘ�����N���X
/// </summary>
#pragma once

class Title :public IGameObject
{
private:
	/// <summary>
	/// �^�C�g���폜��A�����Ƀ��[�h��ʂ�\��������t���[�������̂��߂Ɏg�p����񋓌^�ł��B
	/// </summary>
	enum EnTitleStep
	{
		enTitleStep_1,	// ���[�h��ʂ�NewGO����B
		enTitleStep_2,	// �������Ȃ��i1�t���[���ҋ@�j�B
		enTitleStep_3,	// �^�C�g�����폜����B
	};

public:
	~Title();

private:
	bool Start()override final;
	void Update()override final;
	void Render(RenderContext& rc)override final;

	EnTitleStep m_titleStep;				// ���[�h��ʂ������ɕ\�����邽�߂ɁA�t���[���������s���B
	SpriteRender m_titleViewSpriteRender;	// �^�C�g���摜��`��B
};

