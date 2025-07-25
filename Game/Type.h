/// <summary>
/// �X�^�[�̎�ށA�|�C���g�A�e�L�X�g�I�v�V�������Ǘ�����N���X
/// </summary>
#pragma once

/// <summary>
/// �X�^�[�̎�ނ�\���񋓌^�ł��B
/// </summary>
enum EnStarKinds
{
	enStarKinds_Red,	// ���b�h�X�^�[�B
	enStarKinds_Orange,	// �I�����W�X�^�[�B
	enStarKinds_Purple,	// �p�[�v���X�^�[�B
	enStarKinds_Blue,	// �u���[�X�^�[�B
	enStarKinds_Green,	// �O���[���X�^�[�B
	enStarKinds_Normal,	// �m�[�}���X�^�[�B
	StarKinds_Num
};

/// <summary>
/// �X�^�[�̐F���ƂɈقȂ�|�C���g�l���`����萔�Q�ł��B
/// </summary>
namespace
{
	const int RED_STAR_POINT = 1000;	// ���b�h�X�^�[�|�C���g�B
	const int ORANGE_STAR_POINT = 500;	// �I�����W�X�^�[�|�C���g�B
	const int PURPLE_STAR_POINT = 400;	// �p�[�v���X�^�[�|�C���g�B
	const int BLUE_STAR_POINT = 300;	// �u���[�X�^�[�|�C���g�B
	const int GREEN_STAR_POINT = 200;	// �O���[���X�^�[�|�C���g�B
	const int NORMAL_STAR_POINT = 50;	// �m�[�}���X�^�[�|�C���g�B
};

/// <summary>
/// �t�H���g�����_�[�̐ݒ�B
/// </summary>
/// <param name="pos_x">�`�悷��x���W�B</param>
/// <param name="pos_y">�`�悷��y���W�B</param>
/// <param name="scale">�`�悷��T�C�Y�B</param>
/// <param name="color">�`�悷��F�B</param>
/// <param name="fontRender">�ݒ肷��t�H���g�����_�[�B</param>
/// <param name="format">�`�悷�镶����B</param>
/// <param name="...">�`�悷�镶����𖳌��ɒǉ��ł���B</param>
static void SetTextOption(float pos_x, float pos_y, float scale, Vector4 color, FontRender* fontRender, const wchar_t* format, ...)
{
	fontRender->SetPosition({ pos_x,pos_y,0.0f });
	fontRender->SetScale(scale);
	fontRender->SetColor(color);
	va_list _ArgList;
	__crt_va_start(_ArgList, format);
	wchar_t wcsbuf[256];
	vswprintf_s(wcsbuf, 256, format, _ArgList);
	__crt_va_end(_ArgList);
	fontRender->SetText(wcsbuf);
}