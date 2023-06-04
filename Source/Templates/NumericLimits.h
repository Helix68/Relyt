#pragma once

#include "PrimitiveTypes.h"
#include "Math/MinMax.h"

namespace Rt::Templates
{
	namespace Private
	{
		template <typename NumericType>
		struct NumericLimit;

		template <typename NumericType> struct NumericLimit<const          NumericType> : public NumericLimit<NumericType> { };
		template <typename NumericType> struct NumericLimit<volatile       NumericType> : public NumericLimit<NumericType> { };
		template <typename NumericType> struct NumericLimit<const volatile NumericType> : public NumericLimit<NumericType> { };

		#define DECLARE_NUMERIC_LIMIT(NumType)				\
		template<>											\
		struct NumericLimit<NumType>						\
		{													\
			static constexpr NumType Min = MIN_##NumType;	\
			static constexpr NumType Max = MAX_##NumType;	\
		};

		DECLARE_NUMERIC_LIMIT(uint8);
		DECLARE_NUMERIC_LIMIT(uint16);
		DECLARE_NUMERIC_LIMIT(uint32);
		DECLARE_NUMERIC_LIMIT(uint64);

		DECLARE_NUMERIC_LIMIT(int8);
		DECLARE_NUMERIC_LIMIT(int16);
		DECLARE_NUMERIC_LIMIT(int32);
		DECLARE_NUMERIC_LIMIT(int64);

		DECLARE_NUMERIC_LIMIT(float);
		DECLARE_NUMERIC_LIMIT(double);
	}

	template <typename T>
	using NumericLimit = Private::NumericLimit<T>;
}