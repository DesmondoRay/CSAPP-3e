/* 
 * homework 8.26
 * 
 * 1. 添加回收后台子进程的功能
 * 2. 添加一系列函数，处理作业组，init_jobs(), add_job(pid), delete_job(pid), print_jobs();
 * 3. 添加一个给所有前台进程组中的每个进程发送信号的函数
 * 注: fg和bg命令未完成
 */

#include "../../code/csapp.h"
#include "jobs.h"
#define MAXARGS 128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
void handler1(int sig);
void handler2(int sig);

pid_t bg_pgid, fg_pgid; /* 后台和前台进程组的id */
struct s_job_set *job_set;

int main()
{
	char cmdline[MAXARGS];
	setpgid(0, 0);
	bg_pgid = getpid();
	fg_pgid = getpid() + 1;
	init_jobs();
	
	Signal(SIGINT, handler1);
	Signal(SIGTSTP, handler1);
	Signal(SIGCHLD, handler2);
	
	while (1) {
		/* Read */
		printf("> ");
		Fgets(cmdline, MAXLINE, stdin);
		if (feof(stdin))
			exit(0);
		
		/* Evaluate */
		eval(cmdline);
	}
}

/* handler1 - Send sig to all of foreground process */
void handler1(int sig)
{
	kill(-fg_pgid, sig);
}

/* handler2 - Reaped child process */
void handler2(int sig)
{
	pid_t pid;
	
	int olderrno = errno;
	pid = waitpid(-1, NULL, 0);
	delete_job(pid);
	errno = olderrno;
}

/* eval - Evaluate a command line */
void eval(char *cmdline)
{
	char *argv[MAXARGS]; /* Argument list execve() */
	char buf[MAXLINE];   /* Holds modified command line */
	int bg;				 /* Should the job run in bg or fg? */
	pid_t pid;			 /* Process id */
	sigset_t mask_all, prev_all;

	Sigfillset(&mask_all);
	
	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return;	 /* Ignore empty lines */
	
	if (!builtin_command(argv)) {
		if ((pid = Fork()) == 0) { /* Child runs user job */
			if (!bg)
				setpgid(pid, fg_pgid);  /* foreground process group */
			if (execve(argv[0], argv, environ) < 0) {
				printf("%s: Command not found.\n", argv[0]);
				exit(0);
			}
		}
		
		/* Parent waits for foreground job to terminate */
		if (!bg) {
			int status, sig;
			while ((pid = waitpid(-1, &status, WUNTRACED)) > 0) {
				if (WIFSIGNALED(status)) {  /* 子进程接收到SIGINT信号时 */
					sig = WTERMSIG(status);
					delete_job(pid);
				}
				if (WIFSTOPPED(status))  /* 子进程接收到SIGTSTP信号时 */
					sig = WSTOPSIG(status);
				char s[50];
				sprintf(s, "\nJob %d terminated by signal", pid);
				psignal(sig, s);
			}
		}
		else { /* add background job to job_set */
			Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
			setpgid(pid, bg_pgid);  /* background process group */
			add_job(pid, cmdline);
			printf("[%d] %d %s\t%s", job_set->number, 
				   job_set->jobs[job_set->number-1]->id, 
				   "Running", job_set->jobs[job_set->number-1]->name);
			Sigprocmask(SIG_SETMASK, &prev_all, NULL);
		}
	}
	return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
	if (!strcmp(argv[0], "quit")) { /* quit command */
		free_job_set(); // 释放作业组内存
		exit(0);
	}
	if (!strcmp(argv[0], "jobs")) { /* jobs command */
		print_jobs();
		return 1;
	}
	if (!strcmp(argv[0], "bg")) { /* bg command */
		pid_t pid;
		pid = atoi(&argv[1]);
		Kill(pid, SIGCONT);
		return 1;
	}
	if (!strcmp(argv[0], "fg")) { /* fg command */
		int index, pid;
		if (argv[1][0] == '%')
			index = atoi(&argv[1][1]) - 1;
		// printf("%d\n", index);
		pid = job_set->jobs[index]->id;
		Kill(pid, SIGCONT);
		return 1;
	}
	if (!strcmp(argv[0], "&")) /* Ignore singleton & */
		return 1;
	return 0;					  /* Not a builtin command */
}

/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
	char *delim; 	/* Points to first space delimiter */
	int argc;		/* Number of args */
	int bg;			/* Background job? */
	
	buf[strlen(buf)-1] = ' ';	/* Replace trailing '\n' with space */
	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
		buf++;
	
	/* Build the argv list */
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* Ignore spaces */
			buf++;
	}
	argv[argc] = NULL;
	
	if (argc == 0) /* Ignore blank line */
		return 1;
	
	/* Should the job run in the background? */
	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;
	
	return bg;
}