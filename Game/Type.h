/// <summary>
/// スターの種類、ポイント、テキストオプションを管理するクラス
/// </summary>
#pragma once

/// <summary>
/// スターの種類を表す列挙型です。
/// </summary>
enum EnStarKinds
{
	enStarKinds_Red,	// レッドスター。
	enStarKinds_Orange,	// オレンジスター。
	enStarKinds_Purple,	// パープルスター。
	enStarKinds_Blue,	// ブルースター。
	enStarKinds_Green,	// グリーンスター。
	enStarKinds_Normal,	// ノーマルスター。
	StarKinds_Num
};

/// <summary>
/// スターの色ごとに異なるポイント値を定義する定数群です。
/// </summary>
namespace
{
	const int RED_STAR_POINT = 1000;	// レッドスターポイント。
	const int ORANGE_STAR_POINT = 500;	// オレンジスターポイント。
	const int PURPLE_STAR_POINT = 400;	// パープルスターポイント。
	const int BLUE_STAR_POINT = 300;	// ブルースターポイント。
	const int GREEN_STAR_POINT = 200;	// グリーンスターポイント。
	const int NORMAL_STAR_POINT = 50;	// ノーマルスターポイント。
};

/// <summary>
/// フォントレンダーの設定。
/// </summary>
/// <param name="pos_x">描画するx座標。</param>
/// <param name="pos_y">描画するy座標。</param>
/// <param name="scale">描画するサイズ。</param>
/// <param name="color">描画する色。</param>
/// <param name="fontRender">設定するフォントレンダー。</param>
/// <param name="format">描画する文字列。</param>
/// <param name="...">描画する文字列を無限に追加できる。</param>
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