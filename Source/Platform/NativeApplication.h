#pragma once

#include "CoreTypes.h"

#include "WindowsHWrapper.h"

class RNativeApplication
{
public:

	/* Creates a new instance */
	static RNativeApplication* Create();

	/* Gets the singleton instance */
	static RNativeApplication& Get();

	bool NeedsExit();

	void PumpMessages();

private:
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

	RNativeApplication();

	bool bNeedsExit;
};