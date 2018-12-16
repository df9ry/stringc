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

#include <stdlib.h>
#include <string.h>

#define STRINGC_S_BUFFER 16

struct string
{
	size_t cb;
	union
	{
		char  *pc;
		char   str[STRINGC_S_BUFFER];
	};
};

/**
 * Get C string pointer from a string.
 * @sc string object.
 */
static inline char* string_c(struct string* sc)
{
	return (sc)?((sc->cb)?sc->pc:sc->str):"";
}

static inline size_t string_len(struct string* sc)
{
	return strlen(string_c(sc));
}

/**
 * Allocate a new string as copy of a C string.
 * @c C string as initial value.
 */
extern struct string* string_new_c(char* c);

/**
 * Create duplicate of a string.
 * @sc Source string.
 */
static inline struct string* string_dup(struct string* sc)
{
	return string_new_c(string_c(sc));
}

/**
 * Allocate a new empty string.
 */
static inline struct string* string_new(void)
{
	return string_new_c(NULL);
}

/**
 * Free a string.
 * @sc string to free.
 */
extern void string_free(struct string* sc);

/**
 * Assign C string to string.
 * @sc Target string.
 * @c C string to assign.
 */
extern void string_set_c(struct string* sc, char* c);

/**
 * Assign string to another string.
 * @st Target string.
 * @ss Source string.
 */
static inline void string_set(struct string* st, struct string* ss)
{
	string_set_c(st, string_c(ss));
}

/**
 * Left trim a string in place.
 * @sc string object.
 */
extern void string_ltrim(struct string* sc);

/**
 * Right trim a string in place.
 * @sc string object.
 */
extern void string_rtrim(struct string* sc);

/**
 * Left and right trim a string in place.
 * @sc string object.
 */
static inline void string_trim(struct string* sc)
{
	string_ltrim(sc);
	string_rtrim(sc);
}

/**
 * Add a C string to a string.
 * @sc string object to append to.
 * @c C string to append.
 */
extern void string_add_c(struct string* sc, char* c);

/**
 * Add a string object to a string.
 * @sc string object to append to.
 * @s string object to append.
 */
static inline void string_add(struct string* sc, struct string* s)
{
	string_add_c(sc, string_c(s));
}

/**
 * Cut a range out of a string.
 * @sc string object to cut from, in place.
 * @lpos, left position to start cut from. If negative, count from right.
 * @rpos, right position to cut before. If negative, count from right.
 */
extern void string_range(struct string* sc, int lpos, int rpos);

#endif /* STRINGC_STRINGC_H_ */
