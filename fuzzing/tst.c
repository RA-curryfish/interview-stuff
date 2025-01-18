#include<stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>

void fn(const char* data, size_t size) {
	if(size < 5) return;
	if (data[0] == 'A')  if (data[1] == 'B') if (data[2] == 'C') 
        if (data[3] == 'D') 
	if (data[4] == 'E') 
        *(volatile int *)0 = 0;  // Intentional cras					
}

int main(int argc, char **argv) {
	while (__AFL_LOOP(1000)) {  // Fuzz 1000 iterations before restarting
		char buf[1024];
	        ssize_t len = read(STDIN_FILENO, buf, sizeof(buf));
		if (len > 0) {
	     		fn(buf, len);  // Call the target function
                }
	}
	return 0;
} 
