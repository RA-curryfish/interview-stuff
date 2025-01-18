#include<stdio.h>
#include<stddef.h>

void foo() {
	printf("in foo");
	int x = 10;
	if(x+1>x-5) {}
	printf("after if");
	int y = 8;
	return;
}

int main() {
	char *s = "";
	int a = strlen(s);
	void (*fptr)() = NULL;
	char *buf = malloc(a);
	memcpy(buf,"test",1);
	printf("%d\n",a);
	fptr = foo+a; // modifying indirect jump using library interposer for strlen to skip enbr64 CET (my cpu doesn't support it??)
	printf("%p\n",foo);
	printf("%p\n",fptr);
	fptr();
	return 0;
}
