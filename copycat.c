/* copycat
 * redirects standard input to standard output, making a copy to a file.
 * Copyright (C) 2018 Daniel M. Lima
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * For more information, see <https://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		fputs("copycat redirects stdin to stdout, "
			"making a copy to <filename>.\n"
			"Usage: copycat <filename>\n",
			stderr);
		return -1;
	}
	FILE *out = fopen(argv[1], "r");
	if (out) {
		fprintf(stderr, "[%s] file %s exists, aborting.\n", argv[0], argv[1]);
		fclose(out);
		return -2;
	}
	out = fopen(argv[1], "w");
	if (!out) {
		fprintf(stderr, "[%s] failed to open %s, aborting.\n", argv[0], argv[1]);
		return -3;
	}
	fprintf(stderr, "[%s] copying to %s...\n", argv[0], argv[1]);
	char buf[1024];
	while (fgets(buf, sizeof(buf), stdin)) {
		fputs(buf, stdout);
		fputs(buf, out);
		fflush(out);
	}
	fclose(out);
	return 0;
}
