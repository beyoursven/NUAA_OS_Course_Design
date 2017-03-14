#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int system(const char *command){
	if (command == NULL){
		return 1;
	}
	pid_t pid;
	int status;
	pid = fork();
	if (pid == 0){
		execl("/bin/sh", "sh", "-c", command, (char *)0);
		exit(127);
	}
	else if (pid < 0){
		status = -1;
	}
	else{
		while (waitpid(pid, &status, 0) == -1){
			if (errno != EINTR){
				status = -1;
				break;
			}
		}
	}
	return status;
}

int main(){
	system("ls");
	system("echo dzc is sb");
	return 0;
}
