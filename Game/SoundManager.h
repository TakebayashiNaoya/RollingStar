#pragma once
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

enum EnSoundList {
	enSoundList_TitleBGM,
	enSoundList_InGameBGM,
	enSoundList_SelectSE,
	enSoundList_CountDownSE,
	enSoundList_JumpSE,
	enSoundList_StarGetSE,
	enSoundList_EndSE,
	enSoundList_CallSE,
	enSoundList_Num
};

struct SoundOption {
	const char* filePath;
	bool repeat = false;
	float volume = 0.0f;
};

static SoundSource* sound[enSoundList_Num];

static void SoundNewGO(int a)
{
	SoundOption soundOpt[enSoundList_Num];
	soundOpt[enSoundList_TitleBGM] = { "Assets/sound/title.wav", true, 1.0f };
	soundOpt[enSoundList_InGameBGM] = { "Assets/sound/inGame.wav", true, 1.0f };
	soundOpt[enSoundList_SelectSE] = { "Assets/sound/push.wav", false, 3.5f };
	soundOpt[enSoundList_CountDownSE] = { "Assets/sound/countDownStart.wav", false, 3.5f };
	soundOpt[enSoundList_JumpSE] = { "Assets/sound/jump.wav", false, 3.5f };
	soundOpt[enSoundList_StarGetSE] = { "Assets/sound/star.wav", false, 3.5f };
	soundOpt[enSoundList_EndSE] = { "Assets/sound/end.wav", false, 3.5f };
	soundOpt[enSoundList_CallSE] = { "Assets/sound/call.wav", false, 3.5f };

	sound[a] = NewGO<SoundSource>(0);
	g_soundEngine->ResistWaveFileBank(a, soundOpt[a].filePath);
	sound[a]->Init(a);
	sound[a]->Play(soundOpt[a].repeat);
	sound[a]->SetVolume(soundOpt[a].volume);
}

static void SoundDeleteGO(int a) {
	DeleteGO(sound[a]);
}