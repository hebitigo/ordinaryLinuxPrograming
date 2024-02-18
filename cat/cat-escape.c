#include <stdio.h>
#include <stdlib.h>

void cat(FILE *stream);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cat(stdin);
    }
    else
    {
        int i;
        for (i = 1; i < argc; i++)
        {
            FILE *s = fopen(argv[i], "r");
            if (!s)
            {
                perror(argv[i]);
                exit(1);
            }
            cat(s);
            fclose(s);
        }
        exit(0);
    }
}

void cat(FILE *s)
{
    int c;

    for (;;)
    {
        c = fgetc(s);
        if (c == EOF)
        {
            break;
        }
        switch (c)
        {
        case '\t':
            if (fputs("\\t", stdout) == EOF)
            {
                if (ferror(stdout) != 0)
                {
                    exit(1);
                }
            };
            break;
        case '\n':
            if (fputs("&\n", stdout) == EOF)
            {
                if (ferror(stdout) != 0)
                {
                    exit(1);
                }
            }
            break;
        default:
            if (fputc(c, stdout) == EOF)
                exit(1);
            break;
        }
    }
}