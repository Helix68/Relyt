#pragma once

#include "CoreTypes.h"

#include "WindowsHWrapper.h"

class RNativeWindow
{
public:

	static const TCHAR AppWindowClass[];

	/* Constructs a new instance of RNativeWindow */
	RNativeWindow(const TCHAR* InTitle);

	/* Gets the underlying HWND handle for this window */
	FORCEINLINE HWND GetHWnd() { return HWnd; }

	void Show();

private:
	HWND HWnd;

	bool bIsVisible;

};