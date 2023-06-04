#pragma once

#include "CoreTypes.h"

#include "WindowsHWrapper.h"

class RApplication
{
public:

	static const TCHAR ClassName[];

	/* Creates a new instance */
	static RApplication* Create();

	/* Gets the singleton instance */
	static RApplication& Get();

	bool NeedsExit();

	void PumpMessages();

private:
	static LRESULT CALLBACK StaticWndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam);

	RApplication();

	bool bNeedsExit;
};