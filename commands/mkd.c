#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_error(const char *this, const char *filename)
{ // in case if command fails for some reason
    // this will be name of the command
    fprintf(stderr, "%s: cannot create directory '%s'\n"
                    "ERROR: %s\n",
            this, filename, strerror(errno));

    exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{ // if syntax of command is not correct
    fprintf(stderr, "SYNTAX ERROR: "
                    "USAGE %s [filename]\n",
            this);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        print_usage(argv[0]);
    }

    if (mkdir(argv[1], 0760) == -1)
    {
        print_error(argv[0], argv[1]);
    }

    return 0;
}
