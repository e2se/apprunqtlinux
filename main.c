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
#include <sys/auxv.h>

int main(int argc, char* argv[])
{
	char realbin[PATH_MAX];
	char argv0[PATH_MAX];

	char* currbin = realpath("/proc/self/exe", NULL);

	if (currbin)
	{
		strcpy(realbin, dirname(currbin));
		strcpy(argv0, "/proc/self/exe");
		// fprintf(stdout, "strategy: 1\n");
	}
	else
	{
		const char* currbin = (const char *)getauxval(AT_EXECFN);

		if (currbin && *currbin == '/')
		{
			char* cbin = strdup(currbin); 
			strcpy(realbin, dirname(cbin));
			free(cbin);
			// fprintf(stdout, "strategy: 2\n");
		}
		else 
		{
			const char* currbin = getenv("APPDIR");

			if (currbin)
			{
				strcpy(realbin, currbin);
				// fprintf(stdout, "strategy: 3\n");
			}
			else
			{
				fprintf(stderr, "AppRun: No such file or directory\n");
				return 1;
			}
		}
	}

	free(currbin);

	strcat(realbin, "/AppRun.wrapped");

	if (*argv0 != '\0')
	{
		strcpy(argv0, realbin);
	}

	// fprintf(stdout, "realbin: %s\n", realbin);
	// fprintf(stdout, "argv0: %s\n", argv0);

	// fprintf(stdout, "Running %s\n", realbin);
	
	char* cargv[argc];
	for (int i = 0; i < argc; i++)
	{
		cargv[i] = strdup(argv[i]);
	}
	free(cargv[0]);
	cargv[0] = strdup(argv0);
	cargv[argc] = NULL;

	if (execv(realbin, cargv))
	{
		perror("execv");
		return 1;
	}

	return 0;
}

