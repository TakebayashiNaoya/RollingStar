/// <summary>
/// �T�E���h���Ǘ�����N���X�B
/// </summary>
#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

enum EnSoundList
{
	enSoundList_TitleBGM,		// �^�C�g���ōĐ�����BGM�B
	enSoundList_InGameBGM,		// �C���Q�[���ōĐ�����BGM�B
	enSoundList_SelectSE,		// PUSH(A)��A���������Ƃ��ɍĐ�����SE�B
	enSoundList_CountDownSE,	// �Q�[���J�n���ɍĐ�����J�E���g�_�E����SE�B
	enSoundList_JumpSE,			// �v���C���[���W�����v�����Ƃ��ɍĐ�����SE�B
	enSoundList_StarGetSE,		// �X�^�[���擾�����Ƃ��ɍĐ�����SE�B
	enSoundList_EndSE,			// �^�C���A�b�v�ŏI������Ƃ��ɍĐ�����SE�B
	enSoundList_CallSE,			// ���U���g�\�����ɍĐ����銽��SE�B
	enSoundList_Num
};

class SoundManager :public IGameObject
{
public:
	/// <summary>
	/// �V�����Q�[���I�u�W�F�N�g�̃T�E���h���J�n���܂��B
	/// </summary>
	/// <param name="a">�T�E���h���J�n����Q�[���I�u�W�F�N�g�̎��ʎq�B</param>
	void SoundNewGO(int a);

	/// <summary>
	/// �w�肳�ꂽID�̃T�E���h�I�u�W�F�N�g���폜���܂��B
	/// </summary>
	/// <param name="a">�폜����T�E���h�I�u�W�F�N�g��ID�B</param>
	void SoundDeleteGO(int a);

private:
	SoundSource* sound[enSoundList_Num];
};

