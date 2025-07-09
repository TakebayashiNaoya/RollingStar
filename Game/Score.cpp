#include "stdafx.h"
#include "Score.h"
#include"Star.h"
#include"Game.h"
#include"Type.h"

Score::Score()
{

}

Score::~Score()
{

}

bool Score::Start()
{
	m_star = FindGO<Star>("star");
	m_game = FindGO<Game>("game");

	SpriteRenderList();

	//�u�X�R�A�v�\��
	m_scoreFontRender.SetText(L"�X�R�A");					//�e�L�X�g�\��
	m_scoreFontRender.SetPosition(400.0f, 500.0f, 0.0f);	//���W
	m_scoreFontRender.SetScale(1.5f);						//�T�C�Y
	m_scoreFontRender.SetColor(g_vec4Yellow);				//�F

	return true;
}

void Score::Update()
{
	/*�`���[�g���A���`���U���g�̊ԁA��ɃX�e�[�W�ƃv���C���[�͕\������B
	�@�C���Q�[���i�X�^�[�g�`�I���j�̊Ԃ����X�R�A��\�����邽�߂Ƀt���O�ŊǗ�����B*/
	if (m_game->m_gameEndFlag == true) { return; }		//�Q�[���I���̃t���O
	if (m_game->m_gameStartFlag == false) { return; }	//�Q�[���J�n�̃t���O

	//���v�X�R�A�v�Z
	TotalScoreCalc();

	//���v�X�R�A�\��
	wchar_t tmp[256];
	swprintf_s(tmp, 256, L"%d", m_totalScore);
	m_totalScoreFontRender.SetText(tmp);
	m_totalScoreFontRender.SetPosition({ 410.0f,430.0f ,0.0f });
	m_totalScoreFontRender.SetScale(1.5f);
	m_totalScoreFontRender.SetColor(g_vec4Yellow);

	/// <summary>
	/// �e�L�X�g�ݒ�B
	/// </summary>
	/// {�\���������ϐ�(int�̂�) , x���W , y���W , �T�C�Y , �F}
	FontOption text[StarKinds_Num];
	text[enStarKinds_Red] = { m_starCount[enStarKinds_Red],-850.0f,420.0f,1.3f,g_vec4White };
	text[enStarKinds_Orange] = { m_starCount[enStarKinds_Orange],-850.0f,370.0f,1.3f,g_vec4White };
	text[enStarKinds_Purple] = { m_starCount[enStarKinds_Purple],-850.0f,320.0f,1.3f,g_vec4White };
	text[enStarKinds_Blue] = { m_starCount[enStarKinds_Blue],-850.0f,270.0f,1.3f,g_vec4White };
	text[enStarKinds_Green] = { m_starCount[enStarKinds_Green],-850.0f,220.0f,1.3f,g_vec4White };
	text[enStarKinds_Normal] = { m_starCount[enStarKinds_Normal],-850.0f,170.0f,1.3f,g_vec4White };

	for (int i = 0; i < StarKinds_Num; i++)
	{
		wchar_t tmp[256];
		swprintf_s(tmp, 256, L"%d", text[i].data);
		m_getStarCountFontRender[i].SetText(tmp);										//�e�L�X�g�\��
		m_getStarCountFontRender[i].SetPosition({ text[i].pos_x,text[i].pos_y ,0 });	//���W
		m_getStarCountFontRender[i].SetScale(text[i].scale);							//�T�C�Y
		m_getStarCountFontRender[i].SetColor(text[i].textColor);						//�F
	}
}

void Score::Render(RenderContext& rc)
{
	if (m_game->m_gameEndFlag == false) {
		if (m_game->m_gameStartFlag == true) {

			m_scoreFontRender.Draw(rc);
			m_totalScoreFontRender.Draw(rc);

			for (int i = 0; i < StarKinds_Num; i++) {
				m_getStarCountFontRender[i].Draw(rc);
			}

			for (int j = 0; j < StarKinds_Num; j++) {
				m_starSpriteRender[j].Draw(rc);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////
// �������烁�\�b�h�܂Ƃ߁B
///////////////////////////////////////////////////////////////////

/// <summary>
/// �X�v���C�g�����_�[�܂Ƃ�
/// </summary>
void Score::SpriteRenderList()
{
	m_starSpriteRender[enStarKinds_Red].Init("Assets/sprite/redStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Red].SetPosition({ -900,400,0 });

	m_starSpriteRender[enStarKinds_Orange].Init("Assets/sprite/orangeStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Orange].SetPosition({ -900,350,0 });

	m_starSpriteRender[enStarKinds_Purple].Init("Assets/sprite/purpleStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Purple].SetPosition({ -900,300,0 });

	m_starSpriteRender[enStarKinds_Blue].Init("Assets/sprite/blueStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Blue].SetPosition({ -900,250,0 });

	m_starSpriteRender[enStarKinds_Green].Init("Assets/sprite/greenStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Green].SetPosition({ -900,200,0 });

	m_starSpriteRender[enStarKinds_Normal].Init("Assets/sprite/normalStar.dds", 50.0f, 50.0f);
	m_starSpriteRender[enStarKinds_Normal].SetPosition({ -900,150,0 });

	for (int i = 0; i < StarKinds_Num; i++) {
		m_starSpriteRender[i].Update();
	}
}

void Score::TotalScoreCalc()
{
	m_totalScore = m_starCount[enStarKinds_Red] * RED_STAR_POINT
		+ m_starCount[enStarKinds_Orange] * ORANGE_STAR_POINT
		+ m_starCount[enStarKinds_Purple] * PURPLE_STAR_POINT
		+ m_starCount[enStarKinds_Blue] * BLUE_STAR_POINT
		+ m_starCount[enStarKinds_Green] * GREEN_STAR_POINT
		+ m_starCount[enStarKinds_Normal] * NORMAL_STAR_POINT;
}

