#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "framework.h"

void patternScan(const char *filename)
{
    FILE *fp;
    FILE *out;
    char str[200];
    int i = 0;
    int ch;
    int matches = 0;
    time_t t;

    const char *patterns[] =
    {
        "cmd.exe",
        "powershell",
        "CreateRemoteThread",
        "kernel32.dll",
        "http",
        "VirtualAlloc",
        "LoadLibrary",
        "WinExec",
        "socket",
        "CreateProcess",
        "taskkill",
        "reg add"
    };

    int totalPatterns =
        sizeof(patterns) / sizeof(patterns[0]);

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open file: %s\n",
               filename);
        return;
    }

    printf("\n=====================================================\n");
    printf("                  PATTERN SCAN\n");
    printf("=====================================================\n");

    out = fopen("report.txt", "a");

    if (out != NULL)
    {
        time(&t);

        fprintf(out,
                "\n=====================================================\n");
        fprintf(out,
                "PATTERN SCAN REPORT\n");
        fprintf(out,
                "Time: %s",
                ctime(&t));
        fprintf(out,
                "=====================================================\n");
    }

    while ((ch = fgetc(fp)) != EOF)
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

                for (int j = 0;
                     j < totalPatterns;
                     j++)
                {
                    if (strstr(str,
                               patterns[j]))
                    {
                        printf("[WARNING] Found: %s\n",
                               patterns[j]);

                        if (out != NULL)
                        {
                            fprintf(out,
                                    "[WARNING] Found: %s\n",
                                    patterns[j]);
                        }

                        matches++;
                    }
                }
            }

            i = 0;
        }
    }

    /* Check last string at EOF */
    if (i >= 4)
    {
        str[i] = '\0';

        for (int j = 0;
             j < totalPatterns;
             j++)
        {
            if (strstr(str,
                       patterns[j]))
            {
                printf("[WARNING] Found: %s\n",
                       patterns[j]);

                if (out != NULL)
                {
                    fprintf(out,
                            "[WARNING] Found: %s\n",
                            patterns[j]);
                }

                matches++;
            }
        }
    }

    printf("\nTotal suspicious matches: %d\n",
           matches);

    if (out != NULL)
    {
        fprintf(out,
                "\nTotal suspicious matches: %d\n",
                matches);

        fclose(out);
    }

    fclose(fp);
}

void fullAnalysis(const char *filename)
{
    fileInfo(filename);
    hexDump(filename);
    extractStrings(filename);
    patternScan(filename);
}