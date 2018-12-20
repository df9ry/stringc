/*
 *  Project: stringc - File: stringc_test.c
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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[]) {

	{
		struct string s;

		printf("Testing static string functions:\n");
		STRING_INIT(s);
		assert(s.cb == 0);
		assert(string_len(&s) == 0);
		string_set_c(&s, "1234567890abcdefghijklmnopqrstuvwxyz");
		STRING_RESET(s);
		assert(s.cb == 0);
		assert(string_len(&s) == 0);

		printf("OK\n");
	}

	{
		struct string *s, *s2;

		printf("Testing string_new...:\n");

		s = string_new();
		assert(strcmp(string_c(s), "") == 0);
		assert(string_len(s) == 0);
		s2 = string_dup(s);
		assert(strcmp(string_c(s2), "") == 0);
		assert(string_len(s2) == 0);
		string_free(s);
		string_free(s2);

		s = string_new_c("abc");
		assert(strcmp(string_c(s), "abc") == 0);
		assert(string_len(s) == 3);
		s2 = string_dup(s);
		assert(strcmp(string_c(s2), "abc") == 0);
		assert(string_len(s2) == 3);
		string_free(s);
		string_free(s2);

		s = string_new_c("1234567890abcdefghijklmnopqrstuvwxyz");
		assert(strcmp(string_c(s), "1234567890abcdefghijklmnopqrstuvwxyz") == 0);
		assert(string_len(s) == 36);
		s2 = string_dup(s);
		assert(strcmp(string_c(s2), "1234567890abcdefghijklmnopqrstuvwxyz") == 0);
		assert(string_len(s2) == 36);
		string_free(s);
		string_free(s2);

		printf("OK\n");
	}

	{
		struct string *s, *s2;
		s = string_new();
		s2 = string_new();

		printf("Testing string_set...:\n");

		string_set_c(s, "");
		assert(strcmp(string_c(s), "") == 0);
		assert(string_len(s) == 0);
		string_set(s2, s);
		assert(strcmp(string_c(s2), "") == 0);
		assert(string_len(s2) == 0);

		string_set_c(s, "abc");
		assert(strcmp(string_c(s), "abc") == 0);
		assert(string_len(s) == 3);
		string_set(s2, s);
		assert(strcmp(string_c(s2), "abc") == 0);
		assert(string_len(s2) == 3);

		string_set_c(s, "1234567890abcdefghijklmnopqrstuvwxyz");
		assert(strcmp(string_c(s), "1234567890abcdefghijklmnopqrstuvwxyz") == 0);
		assert(string_len(s) == 36);
		string_set(s2, s);
		assert(strcmp(string_c(s2), "1234567890abcdefghijklmnopqrstuvwxyz") == 0);
		assert(string_len(s2) == 36);

		string_free(s);
		string_free(s2);

		printf("OK\n");
	}

	{
		struct string *s;
		s = string_new();

		printf("Testing string_add...:\n");

		string_set_c(s, "");
		string_add_c(s, "abc");
		assert(strcmp(string_c(s), "abc") == 0);

		string_set_c(s, "abc");
		string_add_c(s, "");
		assert(strcmp(string_c(s), "abc") == 0);

		string_set_c(s, "abc");
		string_add_c(s, "def");
		assert(strcmp(string_c(s), "abcdef") == 0);

		string_set_c(s, "abc");
		string_add_c(s, "0123456789abcdef_");
		assert(strcmp(string_c(s), "abc0123456789abcdef_") == 0);

		string_set_c(s, "0123456789abcdef_");
		string_add_c(s, "abc");
		assert(strcmp(string_c(s), "0123456789abcdef_abc") == 0);

		string_set_c(s, "0123456789abcdef_");
		string_add_c(s, "ABCDEFGHIJKLMNOP#");
		assert(strcmp(string_c(s), "0123456789abcdef_ABCDEFGHIJKLMNOP#") == 0);

		string_free(s);
		printf("OK\n");
	}

	{
		struct string *s;
		s = string_new();

		printf("Testing string_...trim:\n");

		string_set_c(s, "");
		string_ltrim(s);
		assert(strcmp(string_c(s), "") == 0);

		string_set_c(s, "");
		string_rtrim(s);
		assert(strcmp(string_c(s), "") == 0);

		string_set_c(s, "");
		string_trim(s);
		assert(strcmp(string_c(s), "") == 0);

		string_set_c(s, " Test ");
		string_ltrim(s);
		assert(strcmp(string_c(s), "Test ") == 0);

		string_set_c(s, " Test ");
		string_rtrim(s);
		assert(strcmp(string_c(s), " Test") == 0);

		string_set_c(s, " Test ");
		string_trim(s);
		assert(strcmp(string_c(s), "Test") == 0);

		string_free(s);
		printf("OK\n");
	}

	{
		struct string *s;
		s = string_new();

		printf("Testing string_range:\n");

		string_set_c(s, "01234567890");
		string_range(s, 0, 0);
		assert(strcmp(string_c(s), "01234567890") == 0);

		string_set_c(s, "01234567890");
		string_range(s, 2, 0);
		assert(strcmp(string_c(s), "234567890") == 0);

		string_set_c(s, "01234567890");
		string_range(s, -3, 0);
		assert(strcmp(string_c(s), "890") == 0);

		string_set_c(s, "01234567890");
		string_range(s, 3, -3);
		assert(strcmp(string_c(s), "34567") == 0);

		string_set_c(s, "01234567890");
		string_range(s, 4, 6);
		assert(strcmp(string_c(s), "45") == 0);

		string_set_c(s, "01234567890");
		string_range(s, 5, 6);
		assert(strcmp(string_c(s), "5") == 0);

		string_set_c(s, "01234567890");
		string_range(s, 7, 4);
		assert(strcmp(string_c(s), "") == 0);

		string_set_c(s, "01234567890");
		string_range(s, -99, 99);
		assert(strcmp(string_c(s), "01234567890") == 0);

		string_free(s);
		printf("OK\n");
	}

	return EXIT_SUCCESS;
}
