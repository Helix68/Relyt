#pragma once

template<typename T32BITS, typename T64BITS, int PointerSize>
struct SelectIntPointerType
{
	// nothing here are is it an error if the partial specializations fail
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 8>
{
	// Select the 64 bit type.
	typedef T64BITS TIntPointer;
};

template<typename T32BITS, typename T64BITS>
struct SelectIntPointerType<T32BITS, T64BITS, 4>
{
	// Select the 32 bit type.
	typedef T32BITS TIntPointer;
};

//~ Unsigned base types

// 8-bit unsigned integer
typedef unsigned char 		uint8;

// 16-bit unsigned integer
typedef unsigned short int	uint16;

// 32-bit unsigned integer
typedef unsigned int		uint32;

// 64-bit unsigned integer
typedef unsigned long long	uint64;

//~ Signed base types.

// 8-bit signed integer
typedef	signed char			int8;

// 16-bit signed integer
typedef signed short int	int16;

// 32-bit signed integer
typedef signed int	 		int32;

// 64-bit signed integer
typedef signed long long	int64;

//~ Character types

// An ANSI character. 8-bit fixed-width representation of 7-bit characters
typedef char				ANSICHAR;

// A wide character. ?-bit fixed-width representation of the platform's natural wide character set
typedef wchar_t				WIDECHAR;

// An 8-bit character type
typedef char8_t				UTF8CHAR;

// A 16-bit character type
typedef char16_t			CHAR16;

// A 32-bit character type
typedef char32_t			CHAR32;

#if UNICODE
/// Either ANSICHAR or WIDECHAR, depending on whether the platform supports wide characters
typedef WIDECHAR			TCHAR;
#else
/// Either ANSICHAR or WIDECHAR, depending on whether the platform supports wide characters
typedef ANSICHAR			TCHAR;
#endif

// Unsigned int. The same size as a pointer
typedef SelectIntPointerType<unsigned long, uint64, sizeof(void*)>::TIntPointer UPTRINT;

// Signed int. The same size as a pointer
typedef SelectIntPointerType<long, int64, sizeof(void*)>::TIntPointer PTRINT;

// Unsigned int. The same size as a pointer
typedef UPTRINT SIZE_T;

// Signed int. The same size as a pointer
typedef PTRINT SSIZE_T;

typedef int32					TYPE_OF_NULL;
typedef decltype(nullptr)		TYPE_OF_NULLPTR;

#define WIDETEXT(x)		L ## x
#define UTF8TEXT(x)		u8 ## x
#define UTF16TEXT(x)	u ## x
#define ANSITEXT(x)		x

#if UNICODE
#define TEXT(x) WIDETEXT(x)
#else
#define TEXT(x) ANSITEXT(x)
#endif
