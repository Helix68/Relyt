#pragma once

// Turns an preprocessor token into a real string (see UBT_COMPILED_PLATFORM)
#define PREPROCESSOR_TO_STRING(x) PREPROCESSOR_TO_STRING_INNER(x)
#define PREPROCESSOR_TO_STRING_INNER(x) #x

// Concatenates two preprocessor tokens, performing macro expansion on them first
#define PREPROCESSOR_JOIN(x, y) PREPROCESSOR_JOIN_INNER(x, y)
#define PREPROCESSOR_JOIN_INNER(x, y) x##y

// Concatenates the first two preprocessor tokens of a variadic list, after performing macro expansion on them
#define PREPROCESSOR_JOIN_FIRST(x, ...) PREPROCESSOR_JOIN_FIRST_INNER(x, __VA_ARGS__)
#define PREPROCESSOR_JOIN_FIRST_INNER(x, ...) x##__VA_ARGS__

// Expands to the second argument or the third argument if the first argument is 1 or 0 respectively
#define PREPROCESSOR_IF(cond, x, y) PREPROCESSOR_JOIN(PREPROCESSOR_IF_INNER_, cond)(x, y)
#define PREPROCESSOR_IF_INNER_1(x, y) x
#define PREPROCESSOR_IF_INNER_0(x, y) y

// Expands to the parameter list of the macro - used to pass a *potentially* comma-separated identifier to another macro as a single parameter
#define PREPROCESSOR_COMMA_SEPARATED(first, ...) first, ##__VA_ARGS__

#define RT_SOURCE_LOCATION TEXT(__FILE__ "(" PREPROCESSOR_TO_STRING(__LINE__) ")")
