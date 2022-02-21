#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>


int main(int argc, char *argv[], char**envp) {
	pid_t id;

	char *cmds[] = {"ls", "-l", NULL};

	id = fork();

	if(id == 0) {
		printf("Hello world from child %d\n", id);

		execve("/usr/bin/ls", cmds, NULL);

		printf("Goodbye from child %d\n", id);
	}
	else {
		printf("Hello world from parent %d\n", id);

		printf("Goodbye from parent %d\n", id);
	}
	int i = 0;
	while(envp[i]) printf("%s\n", envp[i++]);
}