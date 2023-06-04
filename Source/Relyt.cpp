/*
 * Relyt only runs on windows using the MSVC compiler - x64 or x86 architecture.
 */

#include "CoreTypes.h"

#include "Platform/NativeApplication.h"
#include "Platform/NativeWindow.h"
#include "Platform/WindowsHWrapper.h"

#include "Char.h"

int32 WINAPI WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char* pCmdLine, _In_ int32 nCmdShow)
{
    RNativeApplication* App = RNativeApplication::Create();

    RNativeWindow* NativeWindow = new RNativeWindow(TEXT("Relyt"));
    NativeWindow->Show();

    while (!App->NeedsExit())
    {
        App->PumpMessages();
    }

    return 0;
}

