#pragma once

#include "CoreTypes.h"

#include "WindowsHWrapper.h"

class RWindow
{
public:

	/* Constructs a new instance of RNativeWindow */
	RWindow(const TCHAR* InTitle);

	/* Gets the underlying HWND handle for this window */
	FORCEINLINE HWND GetHWnd() { return HWnd; }

	/* Shows the window to the desktop */
	void Show();

	/* Hides the window from the desktop */
	void Hide();

	/* Tells the window to takeup the whole desktop, excluding taskbar */
	void Maximize();
	bool IsMaximized();

	/* Hides the window from the desktop without removing it from the taskbar */
	void Minimize();
	bool IsMinimized();

	/* Returns whether or not the window is current visible */
	bool IsVisible();

	/* Sets the window title */
	void SetTitle(const TCHAR* Title);

private:
	HWND HWnd;

	bool bIsVisible;

};