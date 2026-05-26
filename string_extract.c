#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "framework.h"

void extractStrings(const char *filename)
{
    FILE *fp;
    FILE *out;
    unsigned char ch;
    char str[200];
    int i = 0;
    int count = 0;
    time_t t;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open file: %s\n",
               filename);
        return;
    }

    printf("\n=====================================================\n");
    printf("                 EXTRACTED STRINGS\n");
    printf("=====================================================\n");

    out = fopen("report.txt", "a");

    if (out != NULL)
    {
        time(&t);

        fprintf(out,
                "\n=====================================================\n");
        fprintf(out,
                "STRING EXTRACTION REPORT\n");
        fprintf(out,
                "Time: %s",
                ctime(&t));
        fprintf(out,
                "=====================================================\n");
    }

    while (fread(&ch, 1, 1, fp) == 1)
    {
        if (isprint(ch))
        {
            if (i < 199)
            {
                str[i++] = ch;
            }
        }
        else
        {
            if (i >= 4)
            {
                str[i] = '\0';
                count++;

                printf("%3d. %s\n",
                       count,
                       str);

                if (out != NULL)
                {
                    fprintf(out,
                            "%3d. %s\n",
                            count,
                            str);
                }
            }

            i = 0;
        }
    }

    /* Check last string at EOF */
    if (i >= 4)
    {
        str[i] = '\0';
        count++;

        printf("%3d. %s\n",
               count,
               str);

        if (out != NULL)
        {
            fprintf(out,
                    "%3d. %s\n",
                    count,
                    str);
        }
    }

    printf("\nTotal strings found: %d\n",
           count);

    if (out != NULL)
    {
        fprintf(out,
                "\nTotal strings found: %d\n",
                count);

        fclose(out);
    }

    fclose(fp);
}