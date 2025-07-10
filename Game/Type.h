#pragma once

enum EnStarKinds {
	enStarKinds_Red,
	enStarKinds_Orange,
	enStarKinds_Purple,
	enStarKinds_Blue,
	enStarKinds_Green,
	enStarKinds_Normal,
	StarKinds_Num
};

namespace {
	const int RED_STAR_POINT = 1000;
	const int ORANGE_STAR_POINT = 500;
	const int PURPLE_STAR_POINT = 400;
	const int BLUE_STAR_POINT = 300;
	const int GREEN_STAR_POINT = 200;
	const int NORMAL_STAR_POINT = 50;
};

//(pos_x,pos_y,scale,color,&fontRender,format)
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