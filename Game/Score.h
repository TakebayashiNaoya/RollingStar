/// <summary>
/// �X�R�A���Ǘ�����N���X
/// </summary>
#pragma once
#include "Type.h"

class Game;
class Star;

class Score : public IGameObject
{
public:
	/// <summary>
	/// ���v�X�R�A���擾���܂��B
	/// </summary>
	/// <returns>���v�X�R�A�im_totalScore�j�̒l��Ԃ��܂��B</returns>
	int GetTotalScore()
	{
		return m_totalScore;
	}

	/// <summary>
	/// �w�肳�ꂽ�C���f�b�N�X�ɑΉ����鐯�̐����擾���܂��B
	/// </summary>
	/// <param name="a">���̐����擾���邽�߂̃C���f�b�N�X�B</param>
	/// <returns>�w�肳�ꂽ�C���f�b�N�X�ɑΉ����鐯�̐��iint�^�j�B</returns>
	int GetStarCount(int a)
	{
		return m_starCount[a];
	}

	/// <summary>
	/// �w�肳�ꂽ�C���f�b�N�X�̐��̐��𑝉������܂��B
	/// </summary>
	/// <param name="a">���̐��𑝉�������C���f�b�N�X�B</param>
	void StarCountIncrease(int a)
	{
		m_starCount[a]++;
	}

private:
	bool Start() override final;
	void Update() override final;
	void Render(RenderContext& rc) override final;

	/// <summary>
	/// �X�v���C�g�̃����_�[���X�g���������܂��B
	/// </summary>
	void SpriteRenderList();

	/// <summary>
	/// ���v�X�R�A���v�Z���܂��B
	/// </summary>
	void TotalScoreCalc();

	Game* m_game = nullptr;
	Star* m_star = nullptr;

	SpriteRender m_starSpriteRender[StarKinds_Num];		// �X�^�[�̉摜��`�悷�邽�߂̔z��B
	SpriteRender m_spriteRender[StarKinds_Num];			// 
	FontRender m_getStarCountFontRender[StarKinds_Num];	// 
	FontRender m_totalScoreFontRender;					// 
	FontRender m_scoreFontRender;						// 

	const struct FontOption
	{
		int data = 0;		//�\���������ϐ�
		float pos_x = 0.0f;	//x���W
		float pos_y = 0.0f;	//y���W
		float scale = 0.0f;	//�T�C�Y
		Vector4 textColor;	//�F
	};

	int m_starCount[StarKinds_Num];
	int m_totalScore = 0;
};

