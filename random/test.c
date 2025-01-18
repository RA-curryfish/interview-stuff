#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

int main(int argc, char* argv[], char **envp) {
	printf("%s\n",envp[1]); // env vars are also passed by crt0
	uint64_t *a = malloc(sizeof(uint64_t));	
	
	*a = 0x00010203;
	printf("%d\n",(int)((char*)a)[1]); // gives '2', indicating little endian 

	char* buf = malloc(sizeof(char)*strlen(envp[0]));
	memcpy(buf,envp[0],strlen(envp[0]));
	printf("%s\n", buf);

	free(a);
	free(buf);
	return 0;
}
