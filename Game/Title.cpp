#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "LoadingView.h"

Title::Title()
{

}

Title::~Title()
{
	//BGM���~�߂�
	DeleteGO(m_titleBgm);

	//�C���Q�[����
	m_game = NewGO<Game>(0, "game");
}

bool Title::Start()
{
	m_spriteRender.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);	//�^�C�g���摜�ǂݍ���
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");		//�^�C�g��BGM
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/push.wav");		//�{�^��SE

	//BGM�𗬂�
	m_titleBgm = NewGO<SoundSource>(0);
	m_titleBgm->Init(0);
	m_titleBgm->Play(true);//���[�v�Đ�

	return true;
}

void Title::Update()
{
	//PUSH START�̕\��
	m_fontRender.SetText(L"PUSH (A) START");				//������ݒ肷��B
	m_fontRender.SetPosition({ -470.0f,-200.0f,0.0f });	//�\��������W��ݒ肷��B
	m_fontRender.SetScale(3.0f);						//�����̃T�C�Y
	m_fontRender.SetColor(g_vec4Yellow);				//�\������F��ݒ肷��B

	switch (m_titleStep)
	{
	case Title::enTitleStep_1:
		//A����������I��
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//�{�^��SE
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(6);
			se->Play(false);
			se->SetVolume(3.5f);

			//���[�h��ʂ�\��
			NewGO<LoadingView>(0, "loadingview");

			m_titleStep = enTitleStep_2;
		}
		break;
	case Title::enTitleStep_2:
		//1�t���[���҂���
		m_titleStep = enTitleStep_3;
		break;
	case Title::enTitleStep_3:
		DeleteGO(this);
		break;
	default:
		break;
	}


}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
}