#include<stdio.h>
#include<stddef.h>
// replacing standard strlen and memcpy functions with these for library interposing
// need to compile this like: gcc -shared -fPIC <fname>
// to create shared library and position independant code
// run the application with LD_PRELOAD=./<fname.so> <app>
// for it to use these fns first

static int ctr = 0; 
int strlen(char *s) {
	ctr++;
	return 32;
	return s[0] == '\0'?0:32; // returning random value 
}

void memcpy(char *dest, char *src, size_t len) {
	printf("you've been had :), %d\n", ctr);
	return;
}
