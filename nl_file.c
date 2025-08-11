#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "nl_file.h"

char *nl_readfile(int fd)
{
	struct stat sb;
	int rc = fstat(fd, &sb);
	if (rc < 0)
		return NULL;

	char *data = (char *)calloc(1, sb.st_size + 1);
	if (!data)
		return NULL;

	ssize_t bytes_read = pread(fd, data, sb.st_size, (off_t)0);
	if (bytes_read < 0) {
		perror("nl_readfile pread()");
		return NULL;
	}

	return data;
}
