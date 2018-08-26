/* 
 * homework 8.26
 *
 * 作业组
 */

#include "../../code/csapp.h"
#include "jobs.h"
#define MAXCMDLEN 50

extern struct s_job_set *job_set;

/* 初始化作业组 */
void init_jobs()
{
	job_set = (struct s_job_set *) Malloc(sizeof(struct s_job_set));
	job_set->number = 0;
	return;
}

/* 添加作业 */
int add_job(int pid, char *name)
{
	/* 创建新的作业 */
	struct job *new_job = (struct job *) Malloc(sizeof(struct job));
	char *buf = (char *) Malloc(MAXCMDLEN * sizeof(char));
	strcpy(buf, name);
	new_job->id = pid;
	new_job->name = buf;
	/* 将新的作业添加到作业组 */
	if (job_set->number == MAXJOBS) {
		fprintf(stderr, "jobs more than %d\n", MAXJOBS);
		return 0;
	}
	else {
		job_set->jobs[job_set->number] = new_job;
		job_set->number += 1;
		return 1;
	}
}

/* 删除作业 */
int delete_job(int pid)
{
	int i, j;
	for (i = 0; i < job_set->number; i++) {
		if (pid == job_set->jobs[i]->id) {
			job_set->number -= 1;
			if (job_set->number > 0)
				for (j = i; j < job_set->number; j++)
					job_set->jobs[j] = job_set->jobs[j+1];
			return 1;
		}
	}
	return 0;
}

/* 释放作业组内存, 退出shell时使用 */
void free_job_set()
{
	int i;
	for (i = 0; i < job_set->number; i++)
		Free(job_set->jobs[i]);
	
	Free(job_set);
}

/* 打印作业组内的所有作业 */
// ****** 注： "Running"需要修改，根据进程的状态修改打印"Running"或"Stopped"
void print_jobs()
{
	int i;
	if (job_set->number == 0)
		printf("There is no job in background.\n");
	for (i = 0; i < job_set->number; i++)
		printf("[%d] %d %s\t%s", 
			   i+1, job_set->jobs[i]->id, "Running", job_set->jobs[i]->name);
}

/* 根据索引，获取作业的pid */
pid_t get_job_pid(int index)
{
	
}

/* test */
/*
int main(void)
{
	init_jobs();
	
	add_job(1, "foo 10 &");
	add_job(2, "foo 100 &");
	print_jobs();
	delete_job(2);
	print_jobs();
	free_job_set();
	return 0;
}
*/

/* output: 
[0] 1 Running	foo 10 &
[1] 2 Running	foo 100 &
[0] 1 Running	foo 10 &
*/