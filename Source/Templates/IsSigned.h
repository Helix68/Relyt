#pragma once

#include "PrimitiveTypes.h"

namespace Rt::Templates
{
	namespace Private
	{
		template <typename T>
		struct TIsSigned
		{
			enum { Value = false };
		};

		template <> struct TIsSigned<int8> { enum { Value = true }; };
		template <> struct TIsSigned<int16> { enum { Value = true }; };
		template <> struct TIsSigned<int32> { enum { Value = true }; };
		template <> struct TIsSigned<int64> { enum { Value = true }; };

		template <typename T> struct TIsSigned<const          T> { enum { Value = TIsSigned<T>::Value }; };
		template <typename T> struct TIsSigned<      volatile T> { enum { Value = TIsSigned<T>::Value }; };
		template <typename T> struct TIsSigned<const volatile T> { enum { Value = TIsSigned<T>::Value }; };
	}

	/* Test if a numeric type is signed */
	template <typename T>
	using TIsSigned = Private::TIsSigned<T>::Value;
}
