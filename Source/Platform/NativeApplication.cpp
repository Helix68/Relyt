
#include "NativeApplication.h"

#include "NativeWindow.h"

RNativeApplication* NativeApplication;

RNativeApplication* RNativeApplication::Create()
{
	NativeApplication = new RNativeApplication();
	return NativeApplication;
}

RNativeApplication& RNativeApplication::Get()
{
    return *NativeApplication;
}

bool RNativeApplication::NeedsExit()
{
    return bNeedsExit;
}

void RNativeApplication::PumpMessages()
{
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT RNativeApplication::StaticWndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
    return NativeApplication->WndProc(hwnd, msg, wParam, lParam);
}

LRESULT RNativeApplication::WndProc(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        bNeedsExit = true;
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_KEYDOWN:
    {
        if (wParam == VK_ESCAPE)
        {
            bNeedsExit = true;
            PostQuitMessage(0);
        }
    }
    return 0;

    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

RNativeApplication::RNativeApplication()
    : bNeedsExit(false)
{
    WNDCLASS wc = { };

    wc.lpfnWndProc = StaticWndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = RNativeWindow::AppWindowClass;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);
}
