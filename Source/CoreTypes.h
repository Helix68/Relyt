/*
 * Defines various numeric types and common macros.
 */

#pragma once

#include "PreprocessorHelpers.h"

#ifndef UNICODE
#define UNICODE 0
#endif

//~ Function type macros.

#define VARARGS     __cdecl											/* Functions with variable arguments */
#define CDECL	    __cdecl											/* Standard C function */
#define STDCALL		__stdcall										/* Standard calling convention */
#define FORCEINLINE __forceinline									/* Force code to be inline */
#define FORCENOINLINE __declspec(noinline)							/* Force code to NOT be inline */
#define FUNCTION_NON_NULL_RETURN_START _Ret_notnull_				/* Indicate that the function never returns nullptr. */

/* Use before a function declaration to warn that callers should not ignore the return value */
#define NODISCARD [[nodiscard]]

// Tells the compiler to put the decorated function in a certain section (aka. segment) of the executable.
#define PLATFORM_CODE_SECTION(Name) __declspec(code_seg(Name)) 

#define ABSTRACT abstract
#define CONSTEXPR constexpr
#define MS_ALIGN(n) __declspec(align(n))
#define MSVC_PRAGMA(Pragma) __pragma(Pragma)

#define PLATFORM_BREAK() (__debugbreak())

#if defined( _WIN64 )
// True when compiled for x64, otherwise false when compiling for x86.
#define PLATFORM_64BITS					1
#else
// True when compiled for x64, otherwise false when compiling for x86.
#define PLATFORM_64BITS					0
#endif

// True when compiled for x86, otherwise false when compiling for x64.
#define PLATFORM_32BITS					(!PLATFORM_64BITS)

/* Invalid index */
enum { INDEX_NONE = -1 };

/* Use this enum in a constructor add the ability to force initialization on its members */
enum ForceInitType
{
	ForceInit
};

// Created a variable with a unique name
#define ANONYMOUS_VARIABLE( Name ) PREPROCESSOR_JOIN(Name, __COUNTER__)

/* Thread-safe call once helper for void functions, similar to std::call_once without the std::once_flag */
#define RT_CALL_ONCE(Func, ...) static int32 ANONYMOUS_VARIABLE(ThreadSafeOnce) = ((Func)(__VA_ARGS__), 1)

#include "PrimitiveTypes.h"
