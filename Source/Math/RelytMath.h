#pragma once

#define RT_MATH_USE_INTRINSICS 1

#include "CoreTypes.h"

#include "Templates/TypeCompatibleBytes.h"

#if RT_MATH_USE_INTRINSICS
	#include <xmmintrin.h>
	#include <intrin.h>
#endif // RT_MATH_USE_INTRINSICS

#include <math.h>
#include <float.h>

/* Math functions for Relyt */
struct RMath
{
	//--------------------------------------------------------------------
	//  Standalone Math Functions - don't depend on any other functions.
	//--------------------------------------------------------------------

	/* Computes absolute value */
	template< class T >
	static FORCEINLINE CONSTEXPR T Abs(const T A)
	{
		return (A < (T)0) ? -A : A;
	}

	/* Returns 1, 0, or -1 depending on relation of T to 0 */
	template< class T >
	static FORCEINLINE CONSTEXPR T Sign(const T A)
	{
		return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
	}

	/* Returns higher value */
	template< class T >
	static FORCEINLINE CONSTEXPR T Max(const T A, const T B)
	{
		return (B < A) ? A : B;
	}

	/* Returns lower value */
	template< class T >
	static FORCEINLINE CONSTEXPR T Min(const T A, const T b)
	{
		return (A < B) ? A : B;
	}

	/**
	* Returns an approximation of Exp(-X) based on a Taylor expansion that has had the coefficients adjusted (using
	* optimisation) to minimise the error in the range 0 < X < 1, which is below 0.1%. Note that it returns exactly 1
	* when X is 0, and the return value is greater than the real value for values of X > 1 (but it still tends
	* to zero for large X). 
	*/
	template<class T>
	static CONSTEXPR NODISCARD T InvExpApprox(T X)
	{
		constexpr T A(1.00746054f); // 1 / 1! in Taylor series
		constexpr T B(0.45053901f); // 1 / 2! in Taylor series
		constexpr T C(0.25724632f); // 1 / 3! in Taylor series
		return 1 / (1 + A * X + B * X * X + C * X * X * X);		
	}

	//--------------------------------------------------------------------
	//  Inverse Square Root
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE float InvSqrt(float Value)
	{
		const __m128 One = _mm_set_ss(1.0f);
		const __m128 Y0 = _mm_set_ss(Value);
		const __m128 X0 = _mm_sqrt_ss(Y0);
		const __m128 R0 = _mm_div_ss(One, X0);
		float temp;
		_mm_store_ss(&temp, R0);
		return temp;
	}

	static FORCEINLINE double InvSqrt(double Value)
	{
		const __m128d One = _mm_set_sd(1.0);
		const __m128d Y0 = _mm_set_sd(Value);
		const __m128d X0 = _mm_sqrt_sd(One, Y0);
		const __m128d R0 = _mm_div_sd(One, X0);
		double temp;
		_mm_store_sd(&temp, R0);
		return temp;
	}

	FORCEINLINE float InvSqrtEst(float F)
	{
		// Performs one pass of Newton-Raphson iteration on the hardware estimate
		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, FOver2;
		float temp;

		Y0 = _mm_set_ss(F);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		_mm_store_ss(&temp, X1);
		return temp;
	}

	FORCEINLINE double InvSqrtEst(double InValue)
	{
		return InvSqrt(InValue);
	}
#else
	static FORCEINLINE float InvSqrt(float F) { return 1.0f / sqrtf(F); }
	static FORCEINLINE double InvSqrt(double F) { return 1.0 / sqrt(F); }

	static FORCEINLINE float InvSqrtEst(float F) { return InvSqrt(F); }
	static FORCEINLINE double InvSqrtEst(double F) { return InvSqrt(F); }
#endif // RT_MATH_USE_INTRINSICS

	//--------------------------------------------------------------------
	//  Truncate
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE int32 TruncToInt32(float F)
	{
		return _mm_cvtt_ss2si(_mm_set_ss(F));
	}

	static FORCEINLINE int32 TruncToInt32(double InValue)
	{
		return _mm_cvttsd_si32(_mm_set_sd(InValue));
	}

	static FORCEINLINE int64 TruncToInt64(double InValue)
	{
		return _mm_cvttsd_si64(_mm_set_sd(InValue));
	}

	static FORCEINLINE float TruncToFloat(float F)
	{
		return _mm_cvtss_f32(_mm_round_ps(_mm_set_ss(F), 3));
	}

	static FORCEINLINE double TruncToDouble(double F)
	{
		return _mm_cvtsd_f64(_mm_round_pd(_mm_set_sd(F), 3));
	}

#else
	static FORCEINLINE int32 TruncToInt32(float F) { return (int32)F; }
	static FORCEINLINE int32 TruncToInt32(double F) { return (int32)F; }
	static FORCEINLINE int64 TruncToInt64(double F) { return (int64)F; }

	static FORCEINLINE float  TruncToFloat(float F) { return truncf(F); }
	static FORCEINLINE double TruncToDouble(double F) { return trunc(F); }
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE int32 TruncToInt(float F)    { return TruncToInt32(F); }
	static FORCEINLINE int64 TruncToInt(double F)   { return TruncToInt64(F); }

	//--------------------------------------------------------------------
	//  Floor
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE float FloorToFloat(float A)
	{
		return _mm_cvtss_f32(_mm_floor_ps(_mm_set_ss(A)));
	}

	static FORCEINLINE double FloorToDouble(double A)
	{
		return _mm_cvtsd_f64(_mm_floor_pd(_mm_set_sd(A)));
	}

	static FORCEINLINE int32 FloorToInt32(float A)
	{
		return _mm_cvt_ss2si(_mm_set_ss(A + A - 0.5f)) >> 1;
	}

	static FORCEINLINE int32 FloorToInt32(double A)
	{
		return _mm_cvtsd_si32(_mm_set_sd(A + A - 0.5)) >> 1;
	}

	static FORCEINLINE int64 FloorToInt64(double A)
	{
		return _mm_cvtsd_si64(_mm_set_sd(A + A - 0.5)) >> 1;
	}
#else
	static FORCEINLINE float FloorToFloat(float F) { return floorf(F); }
	static FORCEINLINE double FloorToDouble(double F) { return floor(F); }

	static FORCEINLINE int32 FloorToInt32(float F)
	{
		int32 I = TruncToInt32(F);
		I -= ((float)I > F);
		return I;
	}
	static FORCEINLINE int32 FloorToInt32(double F)
	{
		int32 I = TruncToInt32(F);
		I -= ((double)I > F);
		return I;
	}
	static FORCEINLINE int64 FloorToInt64(double F)
	{
		int64 I = TruncToInt64(F);
		I -= ((double)I > F);
		return I;
	}
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE int32 FloorToInt(float F) { return FloorToInt32(F); }
	static FORCEINLINE int64 FloorToInt(double F) { return FloorToInt64(F); }

	//--------------------------------------------------------------------
	//  Round
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE float FloorToFloat(float F)
	{
		return _mm_cvtss_f32(_mm_floor_ps(_mm_set_ss(F)));
	}

	static FORCEINLINE double FloorToDouble(double F)
	{
		return _mm_cvtsd_f64(_mm_floor_pd(_mm_set_sd(F)));
	}

	static FORCEINLINE float RoundToFloat(float F)
	{
		return FloorToFloat(F + 0.5f);
	}
#else
	static FORCEINLINE float RoundToFloat(float F) { return FloorToFloat(F + 0.5f); }
	static FORCEINLINE double RoundToDouble(double F) { return FloorToDouble(F + 0.5); }
	static FORCEINLINE double RoundToFloat(double F) { return RoundToDouble(F); }
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE int32 RoundToInt32(float F) { return FloorToInt32(F + 0.5f); }
	static FORCEINLINE int32 RoundToInt32(double F) { return FloorToInt32(F + 0.5); }

	static FORCEINLINE int64 RoundToInt64(double F) { return FloorToInt64(F + 0.5); }
	static FORCEINLINE int32 RoundToInt(float F) { return RoundToInt32(F); }
	static FORCEINLINE int64 RoundToInt(double F) { return RoundToInt64(F); }

	//--------------------------------------------------------------------
	//  Ceil
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE float CeilToFloat(float F)
	{
		return _mm_cvtss_f32(_mm_ceil_ps(_mm_set_ss(F)));
	}

	static FORCEINLINE double CeilToDouble(double F)
	{
		return _mm_cvtsd_f64(_mm_ceil_pd(_mm_set_sd(F)));
	}
#else
	static FORCEINLINE float CeilToFloat(float F) { return ceilf(F); }
	static FORCEINLINE double CeilToDouble(double F) { return ceil(F); }
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE int32 CeilToInt32(float F)
	{
		int32 I = TruncToInt32(F);
		I += ((float)I < F);
		return I;
	}

	static FORCEINLINE int32 CeilToInt32(double F)
	{
		int32 I = TruncToInt32(F);
		I += ((double)I < F);
		return I;
	}

	static FORCEINLINE int64 CeilToInt64(double F)
	{
		int64 I = TruncToInt64(F);
		I += ((double)I < F);
		return I;
	}

	static FORCEINLINE int32 CeilToInt(float F) { return CeilToInt32(F); }
	static FORCEINLINE int64 CeilToInt(double F) { return CeilToInt64(F); }

	//--------------------------------------------------------------------
	//  Floating Point
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE bool IsNaN(float A) { return _isnan(A) != 0; }
	static FORCEINLINE bool IsNaN(double A) { return _isnan(A) != 0; }
	static FORCEINLINE bool IsFinite(float A) { return _finite(A) != 0; }
	static FORCEINLINE bool IsFinite(double A) { return _finite(A) != 0; }
#else
	static FORCEINLINE bool IsNaN(float A)
	{
		return (BitCast<uint32>(A) & 0x7FFFFFFFU) > 0x7F800000U;
	}
	static FORCEINLINE bool IsNaN(double A)
	{
		return (BitCast<uint64>(A) & 0x7FFFFFFFFFFFFFFFULL) > 0x7FF0000000000000ULL;
	}

	static FORCEINLINE bool IsFinite(float A)
	{
		return (BitCast<uint32>(A) & 0x7F800000U) != 0x7F800000U;
	}
	static FORCEINLINE bool IsFinite(double A)
	{
		return (BitCast<uint64>(A) & 0x7FF0000000000000ULL) != 0x7FF0000000000000ULL;
	}
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE bool IsNegativeOrNegativeZero(float A)
	{
		return BitCast<uint32>(A) >= (uint32)0x80000000; // Detects sign bit.
	}

	static FORCEINLINE bool IsNegativeOrNegativeZero(double A)
	{
		return BitCast<uint64>(A) >= (uint64)0x8000000000000000; // Detects sign bit.
	}

	//--------------------------------------------------------------------
	//  Random
	//--------------------------------------------------------------------

	static FORCEINLINE int32 Rand() { return rand(); }
	static FORCEINLINE void RandInit(int32 Seed) { srand(Seed); }
	static FORCEINLINE float FRand()
	{
		// FP32 mantissa can only represent 24 bits before losing precision
		constexpr int32 RandMax = 0x00ffffff < RAND_MAX ? 0x00ffffff : RAND_MAX;
		return (Rand() & RandMax) / (float)RandMax;
	}

	//--------------------------------------------------------------------
	//  Floor Log
	//--------------------------------------------------------------------

	static FORCEINLINE uint32 FloorLog2(uint32 Value)
	{
		uint32 pos = 0;
		if (Value >= 1 << 16) { Value >>= 16; pos += 16; }
		if (Value >= 1 << 8)  { Value >>= 8;  pos += 8; }
		if (Value >= 1 << 4)  { Value >>= 4;  pos += 4; }
		if (Value >= 1 << 2)  { Value >>= 2;  pos += 2; }
		if (Value >= 1 << 1)  { pos += 1; }
		return pos;
	}

	static FORCEINLINE uint64 FloorLog2_64(uint64 Value)
	{
		uint64 pos = 0;
		if (Value >= 1ull << 32) { Value >>= 32; pos += 32; }
		if (Value >= 1ull << 16) { Value >>= 16; pos += 16; }
		if (Value >= 1ull << 8)  { Value >>= 8;  pos += 8; }
		if (Value >= 1ull << 4)  { Value >>= 4;  pos += 4; }
		if (Value >= 1ull << 2)  { Value >>= 2;  pos += 2; }
		if (Value >= 1ull << 1)  { pos += 1; }
		return pos;
	}

	//--------------------------------------------------------------------
	//  Count Zeros
	//--------------------------------------------------------------------

#if RT_MATH_USE_INTRINSICS
	static FORCEINLINE uint8 CountLeadingZeros8(uint8 Value)
	{
		unsigned long BitIndex;
		_BitScanReverse(&BitIndex, uint32(Value) * 2 + 1);
		return uint8(8 - BitIndex);
	}

	static FORCEINLINE uint32 CountTrailingZeros(uint32 Value)
	{
		// return 32 if value was 0
		unsigned long BitIndex;	// 0-based, where the LSB is 0 and MSB is 31
		return _BitScanForward(&BitIndex, Value) ? BitIndex : 32;
	}
#else
	static FORCEINLINE uint8 CountLeadingZeros8(uint8 Value)
	{
		if (Value == 0) return 8;
		return uint8(7 - FloorLog2(uint32(Value)));
	}

	static FORCEINLINE uint32 CountTrailingZeros(uint32 Value)
	{
		if (Value == 0)
		{
			return 32;
		}
		uint32 Result = 0;
		while ((Value & 1) == 0)
		{
			Value >>= 1;
			++Result;
		}
		return Result;
	}
#endif // RT_MATH_USE_INTRINSICS

	static FORCEINLINE uint32 CountLeadingZeros(uint32 Value)
	{
		if (Value == 0) return 32;
		return 31 - FloorLog2(Value);
	}

	static FORCEINLINE uint64 CountLeadingZeros64(uint64 Value)
	{
		if (Value == 0) return 64;
		return 63 - FloorLog2_64(Value);
	}

	static FORCEINLINE uint64 CountTrailingZeros64(uint64 Value)
	{
		if (Value == 0)
		{
			return 64;
		}
		uint64 Result = 0;
		while ((Value & 1) == 0)
		{
			Value >>= 1;
			++Result;
		}
		return Result;
	}
};