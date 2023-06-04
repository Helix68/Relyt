#pragma once

#include "PrimitiveTypes.h"

#include <type_traits>

namespace Rt::Templates
{
	/* Used to declare an untyped array of data with compile-time alignment */
	template<int32 Size, uint32 Alignment>
	struct AlignedBytes
	{
		alignas(Alignment) uint8 Pad[Size];
	};

	/* An untyped array of data with compile-time alignment and size derived from another type */
	template<typename ElementType>
	struct TTypeCompatibleBytes
	{
		using ElementTypeAlias_NatVisHelper = ElementType;
		ElementType* GetTypedPtr() { return (ElementType*)this; }
		const ElementType* GetTypedPtr() const { return (const ElementType*)this; }

		alignas(ElementType) uint8 Pad[sizeof(ElementType)];
	};
}

template <
	typename ToType,
	typename FromType,
	std::enable_if_t<sizeof(ToType) == sizeof(FromType) && std::is_trivially_copyable_v<ToType>&& std::is_trivially_copyable_v<FromType>>* = nullptr
>
inline ToType BitCast(const FromType & From)
{
	return __builtin_bit_cast(ToType, From);
}