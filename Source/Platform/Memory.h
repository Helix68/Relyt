#pragma once

#define RT_MEMORY_USE_ALIGNMENT 1

#include "CoreTypes.h"

#include <memory>

/* Contains static functions for [re]allocating, moving, copying, setting, and freeing memory */
struct RMemory
{
	enum
	{
		// Default allocator alignment. If the default is specified, the allocator applies to engine rules.
		// Blocks >= 16 bytes will be 16-byte-aligned, Blocks < 16 will be 8-byte aligned. If the allocator does
		// not support allocation alignment, the alignment will be ignored.
		DEFAULT_ALIGNMENT = 0,

		// Minimum allocator alignment
		MIN_ALIGNMENT = 8,
	};

	/* Moves memory from one Src to Dest */
	static FORCEINLINE void* Memmove(void* Dest, const void* Src, SIZE_T Count)
	{
		return memmove(Dest, Src, Count);
	}

	/* Compares Buf1 to Buf2 */
	static FORCEINLINE int32 Memcmp(const void* Buf1, const void* Buf2, SIZE_T Count)
	{
		return memcmp(Buf1, Buf2, Count);
	}

	/* Sets memory at Dest to the specified Char */
	static FORCEINLINE void* Memset(void* Dest, uint8 Char, SIZE_T Count)
	{
		return memset(Dest, Char, Count);
	}

	/* Zeros out all memory at Dest of Count */
	static FORCEINLINE void* Memzero(void* Dest, SIZE_T Count)
	{
		return memset(Dest, 0, Count);
	}

	/* Copys memory from Src to Dest of Count */
	static FORCEINLINE void* Memcpy(void* Dest, const void* Src, SIZE_T Count)
	{
		return memcpy(Dest, Src, Count);
	}

	static void* Malloc(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT)
	{
#if RT_MEMORY_USE_ALIGNMENT
		return ::_aligned_malloc(Count, Alignment == DEFAULT_ALIGNMENT ? (Count >= 16 ? 16 : 8) : Alignment);
#else
		return ::malloc(Count);
#endif // RT_MEMORY_USE_ALIGNMENT
	}

	static void* Realloc(void* Original, SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT)
	{
#if RT_MEMORY_USE_ALIGNMENT
		return ::_aligned_realloc(Original, Count, Alignment == DEFAULT_ALIGNMENT ? (Count >= 16 ? 16 : 8) : Alignment);
#else
		return ::realloc(Original, Count);
#endif // RT_MEMORY_USE_ALIGNMENT
	}

	static void Free(void* Original)
	{
#if RT_MEMORY_USE_ALIGNMENT
		return ::_aligned_free(Original);
#else
		return ::free(Original);
#endif // RT_MEMORY_USE_ALIGNMENT
	}

	static FORCEINLINE void* MallocZeroed(SIZE_T Count, uint32 Alignment = DEFAULT_ALIGNMENT)
	{
		void* Memory = Malloc(Count, Alignment);
		Memzero(Memory, Count);
		return Memory;
	}
};