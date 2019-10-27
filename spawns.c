#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct globalArgs_t{
	char * method;
	char * enviroment;
	int wait_mode;
	int behavior;
	char * arguments;
	char * path;
	char * file;
};

static const char *optString = "m:e:a:wb:h?";


void globalArgs_init(struct globalArgs_t * arg){
	arg->method = NULL;
	arg->enviroment = NULL;
	arg->wait_mode = 0;
	arg->behavior = 1;
	arg->arguments = NULL;
	arg->path = "/home/RTOSLab/lab2/child";
	arg->file = "child";
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
	return enviroment;
}

void usage(){
	puts("Usage: spawns [OPTION]\n\
\n\
Programm to execute process spawn programms\n\
-m method   spawn* or exec* method\n\
-e env		enviroment variable for child process\n\
-a arg		args for child process\n\
-w 			call wait() func\n\
-b mode 	behavior mode for child process\n\
\n\
Parametrs:\n\
parametr method can take the following values: \
spawn, spawnl, spawnle, spawnlp, spawnlpe, spawnp,spawnv, spawnve, \
spawnvp, spawnvpe, execl, execle, execlp, execlpe, execv, execve, \
execvp, execvpe, fork.\n\
\n\
parametr env must be in form: \n\
variable=value\n\
\n\
parametr arg can be arbitary\n\
\n\
parametr mode can take the following values: \
wait, nowait, nowaito, overlay\n\
");
}

void print_stats(struct globalArgs_t * arg, char ** envp){
	printf("Parent process\n\
--------------\n\
Method: %s %s\n\
PID = [%d] || PPID = [%d]\n\
==============\n\
Send to child:\n\
==============\n\
Argv[0] = %s;\n\
Argv[1] = %s;\n\
Env = %s\n\
==============\n\
My enviroment
==============\n\
Env = %s\n\
",arg->method, arg->wait_mode?"with wait":"without wait", getpid(),getppid(),arg->file,\
		arg->arguments == NULL? "nothing send": arg->arguments,\
		arg->enviroment == NULL? "nothing send": arg->enviroment,\
		get_enviroment(envp));
}

int main(int * argc, char ** argv, char ** envp){
	int opt = 0;
	struct globalArgs_t * globalArgs = malloc(1024);
	globalArgs_init(globalArgs);
	while((opt = getopt(argc,argv,optString))!=-1){
		switch(opt){
			case 'm':
				globalArgs->method = optarg; 
				break;
			case 'e':
				if(strchr(optarg,'=') != NULL){
					globalArgs->enviroment = optarg;
				}
				else{
					printf("\
Wrong format of enviroment variable\n\
Enviroment variable must be in form\n\
\n\
variable=value\n\
");
					return -1;
				}
				break;
			case 'a':
				globalArgs->arguments = optarg;
				break;
			case 'w':
				globalArgs->wait_mode = 1;
				break;
			case 'b':
				if(strcmp(opt,"wait")==0)
					globalArgs->behavior = 0;
				else if (strcmp(opt,"nowait")==0)
					globalArgs->behavior = 1;
				else if (strcmp(opt,"nowaito")==0)
					globalArgs->behavior = 3;
				else if (strcmp(opt,"overlay")==0)
					globalArgs->behavior = 2;
				else {
					printf("Wrong mode!\n");
					return -1;
				}
				break;
			case 'h':
			case '?':
				usage();
				return 0;
				break;
		}
	}
	if(method_call(globalArgs) == -1) return -1;
	print_stats(globalArgs);
	return 0;
}


int method_call(struct globalArgs_t * arg){
	// printf("Parent process: method %s was chosen!\n",arg->method);	
		if(strcmp(arg->method,"spawn") == 0) {
			spawn_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnl") == 0) {
			spawnl_call();
			return 0;
		}
		else if(strcmp(arg->method,"spawnle") == 0) {
			spawnle_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnlp") == 0) {
			spawnlp_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnlpe") == 0) {
			spawnlpe_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnp") == 0) {
			spawnp_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnv") == 0) {
			spawnv_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnve") == 0) {
			spawnve_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnvp") == 0) {
			spawnvp_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"spawnvpe") == 0) {
			spawnvpe_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execl") == 0) {
			execl_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execle") == 0) {
			execle_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execlp") == 0) {
			execlp_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execlpe") == 0) {
			execlpe_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execv") == 0) {
			execv_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execve") == 0) {
			execve_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execvp") == 0) {
			execvp_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"execvpe") == 0) {
			execvpe_call(arg);
			return 0;
		}
		else if(strcmp(arg->method,"fork") == 0) {
			fork();
			return 0;
		}
	printf("Wrong method name!\n");
	return -1;
}

int spawn_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	spawn(arg->path,0,NULL,NULL,tmpargv,arg->enviroment == NULL?NULL:tmpenv);
	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int spawnl_call(struct globalArgs_t * arg){
	if(arg->arguments != NULL)
		spawnl(arg->behavior,arg->path,arg->file,arg->arguments,NULL);
	else
		spawnl(arg->behavior,arg->path,arg->file,NULL);

	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}


int execl_call(struct globalArgs_t * arg){
	if(arg->arguments != NULL)
		execl(arg->path,arg->path,arg->file,arg->arguments,NULL);
	else
		execl(arg->path,arg->path,arg->file,NULL);
}


int spawnle_call(struct globalArgs_t * arg){
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	//tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	if(arg->arguments != NULL)
		spawnle(arg->behavior,arg->path,arg->file,arg->arguments,NULL,arg->enviroment == NULL?NULL:tmpenv);
	else
		spawnle(arg->behavior,arg->path,arg->file,NULL,arg->enviroment == NULL?NULL:tmpenv);

	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execle_call(struct globalArgs_t * arg){
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	if(arg->arguments != NULL)
		execle(arg->path,arg->file,arg->arguments,NULL,arg->enviroment == NULL?NULL:tmpenv);
	else
		execle(arg->path,arg->file,NULL,arg->enviroment == NULL?NULL:tmpenv);	
}

int spawnlp_call(struct globalArgs_t * arg){
	if(arg->arguments != NULL)
		spawnlp(arg->behavior,arg->file,arg->file,arg->arguments,NULL);
	else
		spawnlp(arg->behavior,arg->file,arg->file,NULL);

	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execlp_call(struct globalArgs_t * arg){
	if(arg->arguments != NULL)
		execlp(arg->file,arg->file,arg->arguments,NULL);
	else
		execlp(arg->file,arg->file,NULL);
}

int spawnlpe_call(struct globalArgs_t * arg){
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	if(arg->arguments != NULL)
		spawnlpe(arg->behavior,arg->file,arg->file,arg->arguments,NULL,arg->enviroment == NULL?NULL:tmpenv);
	else
		spawnlpe(arg->behavior,arg->file,arg->file,NULL,arg->enviroment == NULL?NULL:tmpenv);

	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execlpe_call(struct globalArgs_t * arg){
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	if(arg->arguments != NULL)
		execlpe(arg->file,arg->file,arg->arguments,NULL,arg->enviroment == NULL?NULL:tmpenv);
	else
		execlpe(arg->file,arg->file,NULL,arg->enviroment == NULL?NULL:tmpenv);
}

int spawnp_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	spawnp(arg->file,0,NULL,NULL,tmpargv,arg->enviroment == NULL?NULL:tmpenv);
	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}
int spawnv_call(struct globalArgs_t * arg){
	char ** tmpargv = malloc(sizeof(char) * 3 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	spawnp(arg->behavior,arg->path,tmpargv);
}

int execv_call(struct globalArgs_t * arg){
	char ** tmpargv = malloc(sizeof(char) * 3 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	execv(arg->path,tmpargv);
}

int spawnve_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	spawnve(arg->behavior,arg->path,tmpargv,arg->enviroment == NULL?NULL:tmpenv);
	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execve_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	execve(arg->path,tmpargv,arg->enviroment == NULL?NULL:tmpenv);
}

int spawnvp_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	spawnvp(arg->behavior,arg->file,tmpargv);
		if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execvp_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	execvp(arg->file, tmpargv);
}

int spawnvpe_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	spawnvpe(arg->behavior,arg->file,tmpargv,arg->enviroment == NULL?NULL:tmpenv);
	if(arg->wait_mode){
		wait(NULL);
		return 0;
	}
	else 
		return 0;
}

int execvpe_call(struct globalArgs_t * arg){
	char **tmpargv = malloc(sizeof(char) * 3 * 100);
	char **tmpenv = malloc(sizeof(char) * 2 * 100);
	tmpargv[0] = arg->path;
	tmpargv[1] = NULL;
	if(arg->arguments != NULL){
		tmpargv[1] = arg->arguments;
		tmpargv[2] = NULL;
	}
	// tmpenv = NULL;
	if(arg->enviroment != NULL){
		tmpenv[0] = arg->enviroment;
		tmpenv[1] = NULL;
	}
	execvpe(arg->file, tmpargv, arg->enviroment == NULL?NULL:tmpenv);
}

// int fork_call(struct globalArgs_t * arg){
// 	fork();
// }

	// char method_names *[19] = {
	// 	"spawn",
	// 	"spawnl",
	// 	"spawnle",
	// 	"spawnlp",
	// 	"spawnlpe",
	// 	"spawnp",
	// 	"spawnv",
	// 	"spawnve",
	// 	"spawnvp",
	// 	"spawnvpe",
	// 	"execl",
	// 	"execle",
	// 	"execlp",
	// 	"execlpe",
	// 	"execv",
	// 	"execve",
	// 	"execvp",
	// 	"execvpe",
	// 	"fork"
	// }


// Суффиксы l, v, p, e в именах функций определяют формат и объем аргументов, а также каталоги, в которых нужно искать загружаемую программу:

// l (список). Аргументы командной строки передаются в форме списка arg0, arg1.... argn, NULL. Эту форму используют, если количество аргументов известно;
// v (vector). Аргументы командной строки передаются в форме вектора argv[]. Отдельные аргументы адресуются через argv [0], argv [1]... argv [n]. Последний аргумент (argv [n]) должен быть указателем NULL;
// p (path). Обозначенный по имени файл ищется не только в текущем каталоге, но и в каталогах, определенных переменной среды PATH;
// e (среда). Функция ожидает список переменных среды в виде вектора (envp []) и не использует текущей среды.
//int execl(char *name, char *arg0, ... /*NULL*/);
//int execv(char *name, char *argv[]);
//int execle(char *name, char *arg0, ... /*,NULL,char *envp[]*/);
// int execve(char *name, char *arv[], char *envp[]);
// int execlp(char *name, char *arg0, ... /*NULL*/);
// int execvp(char *name, char *argv[]);

