#pragma once

namespace Rt::Templates
{
	namespace Private
	{
		template <typename T>
		struct IsFloatingPoint
		{
			enum { Value = false };
		};

		template <> struct IsFloatingPoint<float> { enum { Value = true }; };
		template <> struct IsFloatingPoint<double> { enum { Value = true }; };
		template <> struct IsFloatingPoint<long double> { enum { Value = true }; };

		template <typename T> struct IsFloatingPoint<const          T> { enum { Value = IsFloatingPoint<T>::Value }; };
		template <typename T> struct IsFloatingPoint<      volatile T> { enum { Value = IsFloatingPoint<T>::Value }; };
		template <typename T> struct IsFloatingPoint<const volatile T> { enum { Value = IsFloatingPoint<T>::Value }; };
	}

	template <typename T>
	constexpr bool IsFloatingPoint = Private::IsFloatingPoint<T>::Value;
}