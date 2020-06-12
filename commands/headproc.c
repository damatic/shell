#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void print_error(const char *this, const char *filename)
{ // in case if command fails for some reason
    // this will be name of the command
    fprintf(stderr, "%s: cannot print 10 lines of '%s' to terminal\n"
                    "ERROR: %s\n",
            this, filename, strerror(errno));

    exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{ // if syntax of command is not correct
    fprintf(stderr, "SYNTAX ERROR: \n"
                    "USAGE %s [OPTION] [source]\n",
            this);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c;
    FILE *file;
    struct stat stbuf1;
    const int limit = 10;
    int count = 0;
    int flag = 0;

    // Check if fd is open, stdin connected on read end of the pipe
    if (!isatty(fileno(stdin)) && argv[1] == NULL)
    {
        flag++;
        if ((file = fopen("head_temp", "w")) == NULL)
            print_error(argv[0], "head_temp");

        while ((c = getc(stdin)) != EOF)
        {
            fprintf(file, "%c", c);
        }

        fclose(file);
        argv[1] = malloc(sizeof(char) * 50);
        strcpy(argv[1], "head_temp");
    }

    if (stat(argv[1], &stbuf1) == -1)
    { // if source file/dir does not exist
        print_error(argv[0], argv[1]);
    }

    file = fopen(argv[1], "r");

    if (file != NULL)
    {
        while ((c = getc(file)) != EOF && count < limit)
        {
            if (c == '\n')
                count++;
            putchar(c);
        }
    }
    if (flag == 1)
    { // cleaning program in case there was pipe
        fclose(file);
        if (remove("head_temp") == -1)
        {
            perror("cannot remove file 'head_temp'");
        }
        return 0;
    }

    fclose(file);

    return 0;
}
