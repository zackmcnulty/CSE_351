#include<stdio.h>
#include<unistd.h>

int main() {
	
	pid_t pid = fork();
	if (pid == 0) {
		printf("hello from child\n");
	
	} else {
		printf("hello from parent\n");
	}

}
