#pragma once

#include "CoreTypes.h"

/* Stores a color with 8 bits of precision per channel */
struct RColor
{
	union { struct { uint8 B, G, R, A; }; uint32 Bits; };

	RColor() 
	{ }

	RColor(ForceInitType)
		: B(0), G(0), R(0), A(255)
	{ }

	uint32& DWColor(void)       { return Bits; }
	uint32  DWColor(void) const { return Bits; }
};