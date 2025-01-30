#include<stdio.h>
#include<stddef.h>
#include<sys/mman.h>
#include<errno.h>
void foo() {
	printf("in foo");
	int x = 10;
	if(x+1>x-5) {}
	printf("after if\n");
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
        void* p = mmap(0x1000,1000,PROT_EXEC|PROT_READ|PROT_WRITE,MAP_ANON|MAP_SHARED,-1,0);
        *(char*)p = 'e';
        //printf("%d",errno);
        //if(p == MAP_FAILED)
        //   printf("br\n");
        printf("%p,%c\n",p,*(char*)p);
	return 0;
}
