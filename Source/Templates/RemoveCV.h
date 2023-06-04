#pragma once

namespace Rt::Templates
{
	namespace Private
	{
		template <typename T> struct TRemoveCV                   { typedef T Type; };
		template <typename T> struct TRemoveCV<const T>          { typedef T Type; };
		template <typename T> struct TRemoveCV<volatile T>       { typedef T Type; };
		template <typename T> struct TRemoveCV<const volatile T> { typedef T Type; };
	}

	/* Removes any const/volatile qualifiers from a type */
	template <typename T> using TRemoveCV = Private::TRemoveCV<T>::Type;
}
