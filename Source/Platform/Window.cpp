#include "Window.h"

#include "Platform/Application.h"

RWindow::RWindow(const TCHAR* InTitle)
	: HWnd(NULL)
	, bIsVisible(false)
{
	HWnd = CreateWindowEx(
		0,
		RApplication::ClassName,
		InTitle,
		WS_OVERLAPPEDWINDOW,
		100, 100,
		800, 800,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL);
}

void RWindow::Show()
{
	if (!bIsVisible)
	{
		bIsVisible = true;

		::ShowWindow(HWnd, SW_SHOW);
	}
}

void RWindow::Hide()
{
	if (bIsVisible)
	{
		bIsVisible = false;

		::ShowWindow(HWnd, SW_HIDE);
	}
}

void RWindow::Maximize()
{
	::ShowWindow(HWnd, SW_MAXIMIZE);
}

bool RWindow::IsMaximized()
{
	return ::IsZoomed(HWnd);;
}

void RWindow::Minimize()
{
	::ShowWindow(HWnd, SW_MINIMIZE);
}

bool RWindow::IsMinimized()
{
	return ::IsIconic(HWnd);;
}

bool RWindow::IsVisible()
{
	return bIsVisible;
}

void RWindow::SetTitle(const TCHAR* Title)
{
	SetWindowText(HWnd, Title);
}
