#include "syscalls.h"

/**
 * main - entrance to program
 * @arc: Number of arguments
 * @argv: array of arguments
 * @envp: Environ variable
 * Return: returns -1 on fail, else 0
*/

int main(int argc, const char *argv[], char *const envp[])
{
	pid_t child;
	int status;
	struct user_regs_struct regs;

	if (argc < 2)
	{
		fprintf(stderr, "Unsupported number of Arguments\n");
		return (-1);
	}
	child = fork();
	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, child, NULL, NULL);
		execve(argv[1], (char * const *)(argv + 1), (char * const *)envp);
	}
	else
	{
		while (1)
		{
			ptrace(PT_SYSCALL, child, NULL, NULL);
			wait(&status);
			if (WIFEXITED(status))
				break;
			ptrace(PTRACE_GETREGS, child, NULL, &regs);
			printf("%lu\n", (size_t)regs.orig_rax);
		}
	}
	return (0);
}