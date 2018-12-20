/*
 *  Project: string - File: string.h
 *  Copyright (C) 2019 - Tania Hagn - tania@df9ry.de
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef STRINGC_STRINGC_H_
#define STRINGC_STRINGC_H_

/** @file */

#include <stdlib.h>
#include <string.h>

/**
 * @brief Strings that does not exceed this size (including '\0') are stored
 * inside.
 */
#define STRINGC_S_BUFFER 16

/**
 * @brief Internal data structure to represent strings. Avoid to use it directly!
 */
struct string
{
	size_t cb;                        /**< Number of bytes allocated in buffer. */
	union
	{
		char  *pc;                    /**< Pointer to string when buffer is allocated. */
		char   str[STRINGC_S_BUFFER]; /**< String content when no buffer is allocated. */
	};
};

/**
 * @brief Initialize a static allocated string.
 * @param sc String to initialize.
 */
#define STRING_INIT(sc) memset(&sc, 0x00, sizeof(struct string))

/**
 * @brief Get C string pointer from a string.
 * @param sc string object.
 * @return Pointer to C string.
 */
static inline char *string_c(struct string *sc)
{
	return (sc)?((sc->cb)?sc->pc:sc->str):"";
}

/**
 * @brief Get C string pointer from a string.
 * @param sc string object.
 * @return Pointer to C string.
 */
#define STRING_C(sc) string_c(&sc)

/**
 * @brief Get current length of the string.
 * @param sc string object.
 * @return length of the string.
 */
static inline size_t string_len(struct string *sc)
{
	return strlen(string_c(sc));
}

/**
 * @brief Get current length of the string.
 * @param sc string object.
 * @return length of the string.
 */
#define STRING_LEN(sc) string_len(&sc)

/**
 * Allocate a new string as copy of a C string.
 * @param c C string as initial value.
 * @return New allocated string with value of 'c'
 */
extern struct string *string_new_c(char *c);

/**
 * @brief Create duplicate of a string.
 * @param sc Source string.
 * @return New allocated string with value of 'sc'.
 */
static inline struct string *string_dup(struct string *sc)
{
	return string_new_c(string_c(sc));
}

/**
 * @brief Allocate a new empty string.
 * @return New allocated empty string.
 */
static inline struct string *string_new(void)
{
	return string_new_c(NULL);
}

extern void __string_reset(struct string *sc);

/**
 * @brief Reinitialize a string.
 * @param sc String to reinitialize.
 */
#define STRING_RESET(sc) __string_reset(&sc)

/**
 * @brief Free a string.
 * @param sc string to free.
 */
extern void string_free(struct string *sc);

/**
 * @brief Assign C string to string.
 * @param sc Target string.
 * @param c C string to assign.
 */
extern void string_set_c(struct string *sc, char *c);

/**
 * @brief Assign C string to string.
 * @param sc Target string.
 * @param c C string to assign.
 */
#define STRING_SET_C(sc, c) string_set_c(&sc, c)

/**
 * @brief Assign string to another string.
 * @param st Target string.
 * @param ss Source string.
 */
static inline void string_set(struct string *st, struct string *ss)
{
	string_set_c(st, string_c(ss));
}

/**
 * @brief Assign string to another string.
 * @param st Target string.
 * @param ss Source string.
 */
#define STRING_SET(st, ss) string_set(&st, &ss)

/**
 * @brief Left trim a string in place.
 * @param sc string object.
 */
extern void string_ltrim(struct string *sc);

/**
 * @brief Left trim a string in place.
 * @param sc string object.
 */
#define STRING_LTRIM(sc) string_ltrim(&sc)

/**
 * @brief Right trim a string in place.
 * @param sc string object.
 */
extern void string_rtrim(struct string *sc);

/**
 * @brief Right trim a string in place.
 * @param sc string object.
 */
#define STRING_RTRIM(sc) string_rtrim(&sc)

/**
 * @brief Left and right trim a string in place.
 * @param sc string object.
 */
static inline void string_trim(struct string *sc)
{
	string_ltrim(sc);
	string_rtrim(sc);
}

/**
 * @brief Left and right trim a string in place.
 * @param sc string object.
 */
#define STRING_TRIM(sc) string_trim(&sc)

/**
 * @brief Add a C string to a string.
 * @param sc string object to append to.
 * @param c C string to append.
 */
extern void string_add_c(struct string *sc, char *c);

/**
 * @brief Add a C string to a string.
 * @param sc string object to append to.
 * @param c C string to append.
 */
#define STRING_ADD_C(sc, c) string_add_c(&sc, c)

/**
 * @brief Add a char to a string.
 * @param sc string object to append to.
 * @param ch char to append.
 */
extern void string_add_char(struct string *sc, char ch);

/**
 * @brief Add a char to a string.
 * @param sc string object to append to.
 * @param ch char to append.
 */
#define STRING_ADD_CHAR(sc, ch) string_add_char(&sc, ch)

/**
 * @brief Add a string object to a string.
 * @param sc string object to append to.
 * @param s string object to append.
 */
static inline void string_add(struct string *sc, struct string *s)
{
	string_add_c(sc, string_c(s));
}

/**
 * @brief Add a string object to a string.
 * @param sc string object to append to.
 * @param s string object to append.
 */
#define STRING_ADD(sc, s) string_add(&sc, &s)

/**
 * @brief Cut a range out of a string.
 * @param sc string object to cut from, in place.
 * @param lpos left position to start cut from. If negative, count from right.
 * @param rpos right position to cut before. If negative, count from right.
 */
extern void string_range(struct string *sc, int lpos, int rpos);

/**
 * @brief Cut a range out of a string.
 * @param sc string object to cut from, in place.
 * @param lpos left position to start cut from. If negative, count from right.
 * @param rpos right position to cut before. If negative, count from right.
 */
#define STRING_RANGE(sc, lpos, rpos) string_range(&sc, lpos, rpos)

#endif /* STRINGC_STRINGC_H_ */
