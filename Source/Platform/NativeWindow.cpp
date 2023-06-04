#include "NativeWindow.h"

const TCHAR RNativeWindow::AppWindowClass[] = TEXT("RelytWindow");

RNativeWindow::RNativeWindow(const TCHAR* InTitle)
	: HWnd(NULL)
	, bIsVisible(false)
{
	HWnd = CreateWindowEx(
		0,
		AppWindowClass,
		InTitle,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		800, 800,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
}

void RNativeWindow::Show()
{
	if (!bIsVisible)
	{
		bIsVisible = true;

		::ShowWindow(HWnd, SW_SHOW);
	}
}
