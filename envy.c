#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int flag_num[]  = { 120, 1,105, 2,111,3 ,109,4, 97,5, 114,6, 97,7, 123,8, 114,9, 101,10, 118,11, 101, 12,114,13, 115,14, 105,15 ,110,16, 103,17 ,95, 18,105,20, 115,21, 95,22, 102,23, 117,24, 110,25, 95,26, 58, 27,45,28, 125};

char  *var;
char  flag[32];

void ___init(void) __attribute__ ((constructor));

void ___init(void) {
	if (ptrace(PTRACE_TRACEME, 0, 0, 0) < 0) {
		printf ("********** Stack smashing Detected ********\n");
		exit(0); 
	}
	var = getenv("ctor_");
	int j =0;
	for (int i = 0 ; i < 55 ; i+= 2) {
		flag[j] = (char)flag_num[i];
		j++;
	}
	return;
}



int main(int argc, char **argv)
{
	volatile int modified;
	char buffer[64];
	if(var == NULL) {
		perror("Unauthorized access !!!!\n");
		return 0;
	}
	if (!strcmp (var, flag)) {
		printf ("Well done by now u should have ur flag\n");
	}

	modified = 0;

	strcpy(buffer, var);

	if(modified == 0x0d0a0d0a) {
		printf("Oh no ther is a buffer overflow here :(\n");
	} else {
		printf("Try again, you got 0x%08x\n", modified);
	}

}

