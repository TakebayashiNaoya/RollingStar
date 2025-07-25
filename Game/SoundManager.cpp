#include "stdafx.h"
#include "SoundManager.h"

namespace
{
	const char* SOUND_FILE_PATH = "Assets/sound/";	// �T�E���h�̃t�@�C���p�X�B

	struct SoundOption
	{
		const char* fileName;	// �Đ��������t�@�C���̖��O�B
		bool repeat = false;	// ���s�[�g���邩�ǂ����B�itrue=����Afalse=���Ȃ��j
		float volume = 0.0f;	// ���ʁB

		// �T�E���h�̃t�@�C���p�X�Ɗe�T�E���h�̃t�@�C�������������ĕԂ��B
		std::string GetFullPath() const
		{
			return std::string(SOUND_FILE_PATH) + fileName;
		}
	};

	const SoundOption SOUND_OPTIONS[] =
	{
		{ "title.wav", true, 1.0f },
		{ "inGame.wav", true, 1.0f },
		{ "push.wav", false, 3.5f },
		{ "countDownStart.wav", false, 3.5f },
		{ "jump.wav", false, 3.5f },
		{ "star.wav", false, 3.5f },
		{ "end.wav", false, 3.5f },
		{ "call.wav", false, 3.5f },
	};
}

void SoundManager::SoundNewGO(int a)
{
	sound[a] = NewGO<SoundSource>(0);
	g_soundEngine->ResistWaveFileBank(a, SOUND_OPTIONS[a].GetFullPath().c_str());	//c_str��string����const char*�ɕϊ��B
	sound[a]->Init(a);
	sound[a]->Play(SOUND_OPTIONS[a].repeat);
	sound[a]->SetVolume(SOUND_OPTIONS[a].volume);
}

void SoundManager::SoundDeleteGO(int a)
{
	DeleteGO(sound[a]);
}