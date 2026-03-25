/*!
 * apprunqtlinux
 * Tiny AppRun launcher for AppImage and the runtime "AppImage/type2-runtime"
 * 
 * @link https://github.com/e2se/apprunqtlinux
 * @copyright e2 SAT Editor Team
 * @author Leonardo Laureti
 * @license MIT License
 * @license GNU GPLv3 License
 */

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	char currbin[PATH_MAX];
	ssize_t ret = readlink("/proc/self/exe", currbin, PATH_MAX-1);

	if (ret == -1)
	{
		perror("readlink");
		return 1;
	}

	char realbin[PATH_MAX];
	strcpy(realbin, dirname(currbin));
	strcat(realbin, "/AppRun.wrapped");
	
	char* cargv[argc];
	for (int i = 0; i < argc; i++)
	{
		cargv[i] = strdup(argv[i]);
	}
	free(cargv[0]);
	cargv[0] = strdup(realbin);
	cargv[argc] = NULL;

	if (execv(realbin, cargv))
	{
		perror("execv");
		return 1;
	}

	return 0;
}

