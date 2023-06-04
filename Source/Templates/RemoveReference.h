#pragma once

namespace Rt::Templates
{
	namespace Private
	{
		template <typename T> struct RemoveReference      { typedef T Type; };
		template <typename T> struct RemoveReference<T& > { typedef T Type; };
		template <typename T> struct RemoveReference<T&&> { typedef T Type; };
	}

	/* Removes any references from a type */
	template <typename T> using RemoveReference = Private::RemoveReference<T>::Type;
}
