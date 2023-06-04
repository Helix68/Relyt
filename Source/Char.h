/*-----------------------------------------------------------------------------
	Contains functions for getting information about characters
-----------------------------------------------------------------------------*/

#pragma once

#include "PrimitiveTypes.h"

#include <ctype.h>
#include <cwctype>

namespace Rt::Char
{
	namespace Private
	{
		template <typename CharType, const unsigned int Size>
		struct CharBase
		{
			static constexpr CharType LineFeed = (CharType)0xa;
			static constexpr CharType VerticalTab = (CharType)0xb;
			static constexpr CharType FormFeed = (CharType)0xc;
			static constexpr CharType CarriageReturn = (CharType)0xd;
			static constexpr CharType NextLine = (CharType)0x85;
			static constexpr CharType LineSeparator = (CharType)0x2028;
			static constexpr CharType ParagraphSeparator = (CharType)0x2029;

			static bool IsLinebreak(CharType Char)
			{
				return ((uint32(Char) - LineFeed) <= uint32(CarriageReturn - LineFeed)) |
					(Char == NextLine) | (Char == LineSeparator) | (Char == ParagraphSeparator);
			}
		};

		template <typename CharType>
		struct CharBase<CharType, 1>
		{
			static constexpr CharType LineFeed = (CharType)0xa;
			static constexpr CharType VerticalTab = (CharType)0xb;
			static constexpr CharType FormFeed = (CharType)0xc;
			static constexpr CharType CarriageReturn = (CharType)0xd;

			static bool IsLinebreak(CharType Char)
			{
				return ((uint32(Char) - LineFeed) <= uint32(CarriageReturn - LineFeed));
			}
		};

		/* Set of utility functions operating on a single character. */
		template <typename CharType>
		struct RChar : CharBase<CharType, sizeof(CharType)>
		{
			/* Only converts ASCII characters, same as CRT to[w]upper() with standard C locale */
			static CharType ToUpper(CharType Char)
			{
				return (CharType)(ToUnsigned(Char) - ((uint32(Char) - 'a' < 26u) << 5));
			}

			/* Only converts ASCII characters, same as CRT to[w]upper() with standard C locale */
			static CharType ToLower(CharType Char)
			{
				return (CharType)(ToUnsigned(Char) + ((uint32(Char) - 'A' < 26u) << 5));
			}

			static bool IsUpper(CharType Char);
			static bool IsLower(CharType Char);
			static bool IsAlpha(CharType Char);
			static bool IsGraph(CharType Char);
			static bool IsPrint(CharType Char);
			static bool IsPunct(CharType Char);
			static bool IsAlnum(CharType Char);
			static bool IsDigit(CharType Char);
			static bool IsHexDigit(CharType Char);
			static bool IsWhitespace(CharType Char);
			static bool IsControl(CharType Char);

			static bool IsOctDigit(CharType Char)
			{
				return uint32(Char) - '0' < 8u;
			}

			static int32 ConvertCharDigitToInt(CharType Char)
			{
				return static_cast<int32>(Char) - static_cast<int32>('0');
			}

			static bool IsIdentifier(CharType Char)
			{
				return IsAlnum(Char) || IsUnderscore(Char);
			}

			static bool IsUnderscore(CharType Char)
			{
				return Char == LITERAL(CharType, '_');
			}
		};
	}

	typedef Private::RChar<TCHAR>    RChar;
	typedef Private::RChar<WIDECHAR> RCharWide;
	typedef Private::RChar<ANSICHAR> RCharAnsi;

	/*-----------------------------------------------------------------------------
		WIDECHAR specialized functions
	-----------------------------------------------------------------------------*/

	template <> inline bool RCharWide::IsUpper     (WIDECHAR Char) { return iswupper(Char) != 0;  }
	template <> inline bool RCharWide::IsLower     (WIDECHAR Char) { return iswlower(Char) != 0;  }
	template <> inline bool RCharWide::IsAlpha     (WIDECHAR Char) { return iswalpha(Char) != 0;  }
	template <> inline bool RCharWide::IsGraph     (WIDECHAR Char) { return iswgraph(Char) != 0;  }
	template <> inline bool RCharWide::IsPrint     (WIDECHAR Char) { return iswprint(Char) != 0;  }
	template <> inline bool RCharWide::IsPunct     (WIDECHAR Char) { return iswpunct(Char) != 0;  }
	template <> inline bool RCharWide::IsAlnum     (WIDECHAR Char) { return iswalnum(Char) != 0;  }
	template <> inline bool RCharWide::IsDigit     (WIDECHAR Char) { return iswdigit(Char) != 0;  }
	template <> inline bool RCharWide::IsHexDigit  (WIDECHAR Char) { return iswxdigit(Char) != 0; }
	template <> inline bool RCharWide::IsWhitespace(WIDECHAR Char) { return iswspace(Char) != 0;  }
	template <> inline bool RCharWide::IsControl   (WIDECHAR Char) { return iswcntrl(Char) != 0;  }


	/*-----------------------------------------------------------------------------
		ANSICHAR specialized functions
	-----------------------------------------------------------------------------*/

	template <> inline bool RCharAnsi::IsUpper     (ANSICHAR Char) { return isupper((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsLower     (ANSICHAR Char) { return islower((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsAlpha     (ANSICHAR Char) { return isalpha((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsGraph     (ANSICHAR Char) { return isgraph((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsPrint     (ANSICHAR Char) { return isprint((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsPunct     (ANSICHAR Char) { return ispunct((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsAlnum     (ANSICHAR Char) { return isalnum((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsDigit     (ANSICHAR Char) { return isdigit((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsHexDigit  (ANSICHAR Char) { return isxdigit((unsigned char)Char) != 0; }
	template <> inline bool RCharAnsi::IsWhitespace(ANSICHAR Char) { return isspace((unsigned char)Char) != 0;  }
	template <> inline bool RCharAnsi::IsControl   (ANSICHAR Char) { return iscntrl((unsigned char)Char) != 0;  }
}

typedef Rt::Char::RChar     RChar;
typedef Rt::Char::RCharAnsi RCharAnsi;
typedef Rt::Char::RCharWide RCharWide;
