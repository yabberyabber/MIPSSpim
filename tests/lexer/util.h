#ifndef _UTIL_H
#define _UTIL_H

int IsSpace(char m) {
	return m == ' ' || m == '\t';
}

char * TrimString(char *str) {
	char *end;

	while (IsSpace(*str)) {
		str++;
	}

	end = str + strlen(str) - 1;
	while (end >str && IsSpace(*end))
		end--;

	*(end + 1) = '\0';

	return str;
}

#endif
