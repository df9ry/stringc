/*
 *  Project: stringc - File: stringc.c
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

#include "stringc/stringc.h"

#include <assert.h>
#include <ctype.h>

static size_t chunk_size(size_t l) {
	return (((l + 1) / STRINGC_S_BUFFER) + 1) * STRINGC_S_BUFFER;
}

struct string* string_new_c(char* c)
{
	if (!c)
		c = "";
	struct string* s = malloc(sizeof(struct string));
	size_t l = strlen(c);
	if (l < STRINGC_S_BUFFER) {
		s->cb = 0;
		strcpy(s->str, c);
	} else {
		s->cb = chunk_size(l);
		s->pc = malloc(s->cb);
		strcpy(s->pc, c);
	}
	return s;
}

void __string_reset(struct string *sc)
{
	assert(sc);
	if (sc->cb > 0) {
		free(sc->pc);
	}
	STRING_INIT(*sc);
}

void string_free(struct string *sc)
{
	if (!sc)
		return;
	if (sc->cb > 0) {
		free(sc->pc);
	}
	free(sc);
}

void string_set_c(struct string* sc, char* c)
{
	assert(sc);
	if (!c) c = "";
	size_t l = strlen(c);
	if (sc->cb) {
		if (l >= sc->cb) {
			sc->cb = chunk_size(l);
			sc->pc = realloc(sc->pc, sc->cb);
		}
		strcpy(sc->pc, c);
		return;
	}
	if (l >= STRINGC_S_BUFFER) {
		sc->cb = chunk_size(l);
		sc->pc = malloc(sc->cb);
		strcpy(sc->pc, c);
		return;
	}
	strcpy(sc->str, c);
}

void string_add_c(struct string* sc, char* c)
{
	char *pc;

	assert(sc);
	if (!c)
		c = "";
	size_t l = string_len(sc) + strlen(c);
	if (!sc->cb) {
		if (l < STRINGC_S_BUFFER) {
			strcat(sc->str, c);
			return;
		}
		sc->cb = chunk_size(l);
		pc = malloc(sc->cb);
		strcpy(pc, sc->str);
		strcat(pc, c);
		sc->pc = pc;
		return;
	}
	if (l >= sc->cb) {
		sc->cb = chunk_size(l);
		sc->pc = realloc(sc->pc, sc->cb);
	}
	strcat(sc->pc, c);
}

void string_add_char(struct string* sc, char ch)
{
	char buf[2];
	buf[0] = ch;
	buf[1] = '\0';
	string_add_c(sc, buf);
}

void string_ltrim(struct string* sc)
{
	assert(sc);
	char* s = string_c(sc);
	char* s_tmp = s;
	size_t l = strlen(s);
	while (isblank(*s_tmp))	{
	    ++s_tmp;
	    --l;
	}
	memmove(s, s_tmp, l+1);
}

void string_rtrim(struct string* sc)
{
	assert(sc);
	char* s = string_c(sc);
	int p = strlen(s) - 1;
	while ((p > 0) && isblank(s[p-1])) {
	    --p;
	}
	s[p] = '\0';
}

void string_range(struct string* sc, int lpos, int rpos)
{
	assert(sc);
	char* s = string_c(sc);
	int l = strlen(s);
	if (rpos == 0)
		rpos = l;
	if (rpos < 0)
		rpos = l + rpos;
	if (rpos < lpos)
		rpos = lpos;
	if (rpos > l)
		rpos = l;
	s[rpos] = '\0';
	l = rpos;
	if (lpos < 0)
		lpos = l + lpos;
	if (lpos < 0)
		lpos = 0;
	if (lpos > l)
		lpos = l;
	if (lpos > 0) {
		memmove(s, &s[lpos], l - lpos + 1);
	}
}
