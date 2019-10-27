#include <process.h>
#include <stdlib.h>
#include <string.h>

void print_stats(char ** env){
	printf("Child process\n\
-------------\n\
PPID = [%d] || PID = [%d]\n\
Argv[0] = %s\n\
Argv[1] = %s\n\
Env = %s ",getppid(), getpid(),argv[0],argv[1],get_enviroment(env));
}

char * get_enviroment(char ** env){
	char * enviroment = malloc(sizeof(char)* 255);
	char **tmpstr;
	char * thisenv;
	for(tmpstr=env;*tmpstr != NULL; tmpstr++){
		thisenv = *tmpstr;
		strcat(enviroment,thisenv);
		strcat(enviroment,"\n");
	}
}

int main(int argc, char **argv, char **envp){
	print_stats(envp);
	return 0;
}
