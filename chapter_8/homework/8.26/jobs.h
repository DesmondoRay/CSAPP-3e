/* 
 * homework 8.26
 *
 * jobs.h
 */

#define MAXJOBS 10

struct job{
	pid_t id;
	char *name;
};

struct s_job_set {
	int number; /* number of jobs */
	struct job *jobs[MAXJOBS];
};

void init_jobs();
int add_job(int pid, char *name);
int delete_job(int pid);
void free_job_set();
void print_jobs();