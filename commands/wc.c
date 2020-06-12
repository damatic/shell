#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h> // needs for rmdir

#define BUFFER_SIZE_FOR_NAMES 50
#define BUFFER_LENGTH 1024

void print_error(const char *this, const char *filename)
{ // in case if command fails for some reason
    // this will be name of the command
    fprintf(stderr, "%s: cannot count chars/words/lines in '%s'\n"
                    "ERROR: %s\n",
            this, filename, strerror(errno));

    exit(EXIT_FAILURE);
}

void print_usage(const char *this)
{ // if syntax of command is not correct
    fprintf(stderr, "SYNTAX ERROR: \n"
                    "USAGE %s [OPTION] [FILE]\n",
            this);

    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int c;
    FILE *file;
    struct stat stbuf1;
    int count = 0;
    char word[BUFFER_SIZE_FOR_NAMES];
    int flag = 0;

    if (argv[1][0] != '-')
    {
        print_usage(argv[0]);
    }

    if (!isatty(fileno(stdin)) && argv[2] == NULL)
    { // check if fd is open, stdin connected to the read end of the pipe
        flag++;
        if ((file = fopen("pipe_temp", "w")) == NULL)
        {
            print_error(argv[0], "pipe_temp");
        }

        while ((c = getc(stdin)) != EOF)
        {
            fprintf(file, "%c", c);
        }

        fclose(file);
        argv[2] = malloc(sizeof(char) * BUFFER_LENGTH);
        strcpy(argv[2], "pipe_temp");
    }

    if (stat(argv[2], &stbuf1) == -1)
    { // if directory for reading does not exits
        print_error(argv[0], argv[2]);
        return EXIT_FAILURE;
    }

    if ((file = fopen(argv[2], "r")) == NULL)
    {
        print_error(argv[0], argv[2]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-c") == 0)
    {
        while ((c = getc(file)) != EOF)
        {
            if (c != ' ' && c != '\n' && c != '\t')
                count++;
        }
        printf("Number of characters in the file: %d\n", count);
    }

    if (strcmp(argv[1], "-w") == 0)
    {
        while (fscanf(file, "%s", word) == 1)
        {
            count++;
        }
        printf("Number of  \"words\" in the file: %d\n", count);
    }

    if (strcmp(argv[1], "-l") == 0)
    {
        while ((c = getc(file)) != EOF)
        {
            if (c == '\n')
                count++;
        }
        printf("Number of lines in the file: %d\n", count);
    }
    fclose(file);

    if (flag == 1)
    { // cleaning program in case there was pipe
        free(argv[2]);
        if (remove("pipe_temp") == -1)
        {
            perror("ERROR: Cannot remove file 'pipe_temp'");
        }
    }

    return 0;
}
