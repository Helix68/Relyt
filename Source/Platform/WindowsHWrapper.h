#pragma once

#pragma push_macro("MAX_uint8")
#pragma push_macro("MAX_uint16")
#pragma push_macro("MAX_uint32")
#pragma push_macro("MAX_int32")
#pragma push_macro("TEXT")
#pragma push_macro("TRUE")
#pragma push_macro("FALSE")

#ifndef _WINNT_
#undef TEXT
#endif

#define WIN32_LEAN_AND_MEAN

struct IUnknown;

#include <Windows.h>

#undef INT
#undef UINT
#undef DWORD
#undef FLOAT

#pragma pop_macro("MAX_uint8")
#pragma pop_macro("MAX_uint16")
#pragma pop_macro("MAX_uint32")
#pragma pop_macro("MAX_int32")
#pragma pop_macro("TEXT")
#pragma pop_macro("TRUE")
#pragma pop_macro("FALSE")
