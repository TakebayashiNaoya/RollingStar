#pragma once

class Tutorial;

class LoadingView :public IGameObject
{
public:
	LoadingView();
	~LoadingView();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	//���[�h�̒i�K
	enum EnLoadingPhase {
		enLoadingPhase_1,
		enLoadingPhase_2,
		enLoadingPhase_3,
		enLoadingPhase_4,
		enLoadingPhase_5,
		enLoadingPhase_6,
		Phase_Num
	};

	//���[�h���
	SpriteRender m_LoadingSceneSpriteRender;

	//���[�h���ɕ\�����鐯�̔z��
	SpriteRender m_LoadingPhaseSpriteRenders[Phase_Num];

	//���[�h�̒i�K�ɉ����Đ���\��
	bool showLoadingPhases[Phase_Num] = { false };

	//A�{�^���������Ă��������̎���
	FontRender m_pushA_FontRender;
};

