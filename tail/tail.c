#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_LINE_LENGTH 1024

static void tail(FILE *f, int lines);

struct option options[] = {
    {"line", required_argument, NULL, 'n'}, {0, 0, 0, 0}};

int main(int argc, char *argv[])
{
    int lines = 10;
    int opt;
    while ((opt = getopt_long(argc, argv, "n:", options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'n':
            lines = atoi(optarg);
            break;
        case '?':
            fprintf(stderr, "Usage %s [-n LINES] [FILE...]\n", argv[0]);
            exit(1);
        }
    }

    if (optind >= argc)
    {
        fprintf(stderr, "file argument is requred\n");
        exit(1);
    }

    for (int i = optind; i < argc; i++)
    {
        FILE *f;
        f = fopen(argv[i], "r");
        if (!f)
        {
            perror(argv[i]);
            exit(1);
        }
        fprintf(stdout, "file tail of %s\n", argv[i]);
        tail(f, lines);
        fclose(f);
    }
    exit(0);
}

void tail(FILE *f, int displayLines)
{
    char ring_buffer[displayLines][MAX_LINE_LENGTH];
    long current = 0;
    long fileLines = 0;

    while ((fgets(ring_buffer[current], MAX_LINE_LENGTH, f)) != NULL)
    {
        current++;
        if (current >= displayLines)
        {
            current = 0;
        }
        fileLines++;
    }

    if (fileLines < displayLines)
    {
        current = 0;
    }

    for (int n = displayLines; n > 0 && fileLines > 0; n--, fileLines--)
    {
        // printf("current: %ld :", current);
        fprintf(stdout, "%s", ring_buffer[current]);

        current++;
        if (current >= displayLines)
        {
            current = 0;
        }
    }
}
