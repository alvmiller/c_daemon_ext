#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

// https://sandervanderburg.blogspot.com/2020/01/writing-well-behaving-daemon-in-c.html
// https://lloydrochester.com/post/c/unix-daemon-example/
// https://psychocod3r.wordpress.com/2019/03/19/how-to-write-a-daemon-process-in-c/
// https://www.thegeekstuff.com/2012/02/c-daemon-process/

// ps xao pid,ppid,pgid,sid,comm
// ps -A

// gcc -Wall daemon_ext.c -o daemon
// sudo ./daemon

int main(int argc, char *argv[])
{
	int c = 0;
	printf("argc = %d\n", argc);
	if (argc == 2) {
		int val = (int)atol(argv[1]);
		printf("\tval = %d\n", val);
		switch(val) {
		case 0:
			/* FALLTHROUGH */
		case 1:
			/* FALLTHROUGH */
		case 2:
			/* FALLTHROUGH */
		case 3:
			c = val;
			break;
		default:
			break;
		}
	}
	printf("\tc = %d\n", c);
	printf("Daemon...\n");

	if (c == 0) {
		pid_t pid;
		int i;

		pid = fork();
		if (pid == -1)
			return -1;
		else if (pid != 0)
			exit (EXIT_SUCCESS);

		if (setsid() == -1)
			return -1;

		if (chdir("/") == -1)
			return -1;

		//for (i = 0; i < NR_OPEN; i++)
		//    close(i);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		struct rlimit rlim;
		int num_of_fds = getrlimit(RLIMIT_NOFILE, &rlim);
		if(num_of_fds != -1)
			for(i = 3; i < num_of_fds; i++)
				close(i);

		open("/dev/null", O_RDWR);
		dup(0);
		dup(0);
	}
	
	if (c == 1) {
		;
	}

	sleep(60);

    return 0;
}