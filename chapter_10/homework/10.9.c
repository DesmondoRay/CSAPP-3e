/**
 * homework 10.9
 */

if (Fork() == 0) {
	dup2(0, 3);
	Execve("fstatcheck", argv, envp);
}