#include "paint.h"
#include <iostream>
using namespace zzj;
Device::ComposedXY Device::GetDpi()
{
	ComposedXY xy;
	xy.x= GetDeviceCaps(hdc, LOGPIXELSX);
	xy.y= GetDeviceCaps(hdc, LOGPIXELSY);
	return xy;
}



Device::ComposedXY Device::DLUToPixel(Device::ComposedXY dlu)
{
	int baseX = GetBase().x;
	int baseY = GetBase().y;
	ComposedXY ret;
	ret.x = dlu.x * baseX / 4;
	ret.y = dlu.y * baseY / 4;
	return ret;
}

Device::ComposedXY Device::PTToPixel(ComposedXY pt)
{
	ComposedXY ret;
	ComposedXY dpi = GetDpi();

	ret.x = pt.x * dpi.x / 72;
	ret.y = pt.y * dpi.y / 72;
	return ret;
}

HDC Device::GetScreenHDC()
{
	return GetDC(0);
}

HDC Device::GetHDC(HWND wndHandle)
{
	return GetDC(wndHandle);
}

Device::ComposedXY Device::GetBase()
{
	HWND hwnd = WindowFromDC(hdc);
	RECT rc = { 0,0,4,8 };
	MapDialogRect(hwnd, &rc);
	ComposedXY ret;
	ret.x = rc.right;
	ret.y = rc.bottom;

	
	return ret;
}

BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID aFontCount);
void zzj::Font::EnumFontFamilies(HDC hdc)
{
	::EnumFontFamilies(hdc, (LPCWSTR)NULL,
		(FONTENUMPROC)EnumFamCallBack, (LPARAM)NULL);
}
BOOL CALLBACK EnumFamCallBack(LPLOGFONT lplf, LPNEWTEXTMETRIC lpntm, DWORD FontType, LPVOID aFontCount)
{
	std::wstring str = lplf->lfFaceName;
	std::wcout << str << std::endl;
	return true;

	
}
void zzj::Font::EnumFonts(HDC hdc) {
	::EnumFonts(hdc, NULL, (FONTENUMPROC)EnumFamCallBack, NULL);
}