#include "stdafx.h"
#include "ResultView.h"
#include "GameTimer.h"

ResultView::ResultView()
{
	m_endSpriteRender.Init("Assets/sprite/end.dds", 1920.0f, 1080.0f);
	m_backSpriteRender.Init("Assets/sprite/backBlack.dds", 1920.0f, 1080.0f);

	m_spriteRender = &m_endSpriteRender;

}



ResultView::~ResultView()
{

}

//更新処理。

void ResultView::Update()
{
	if (m_isFlag == true) {

		finishCount += g_gameTime->GetFrameDeltaTime();

		if (finishCount >= 3.0f) {
			m_spriteState = 1;
		}

		if (m_spriteState == 0) {
			m_spriteRender = &m_endSpriteRender;
		}

		else if (m_spriteState == 1) {
			m_spriteRender = &m_backSpriteRender;
		}

	}
	//m_spriteRender->Update();

	//背面を暗くする
	//m_spriteRender.Init("Assets/sprite/backBlack.dds", 1920.0f, 1080.0f);

	////Aボタンが押されたら。
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	//タイトルのオブジェクトをつくる。
	//	NewGO<Title>(0, "title");

	//	//自身を削除する。
	//	DeleteGO(this);
	//}
}

//描画処理。
void ResultView::Render(RenderContext& rc)
{
	if (m_isFlag == true) {
		m_spriteRender->Draw(rc);
	}
	//m_endSpriteRender.Draw(rc);
	//m_backSpriteRender.Draw(rc);
	//m_fontRender.Draw(rc);

	//if (finishCount >= 3.0f) {
	//	return;
	//}
	//m_backSpriteRender.Draw(rc);

	//m_endSpriteRender.Draw(rc);


}