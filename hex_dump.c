#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "framework.h"

void hexDump(const char *filename)
{
    FILE *fp;
    FILE *out;
    unsigned char buffer[16];
    int bytesRead;
    int offset = 0;
    time_t t;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open file: %s\n",
               filename);
        return;
    }

    printf("\n=====================================================\n");
    printf("                     HEX DUMP\n");
    printf("=====================================================\n");
    printf("Offset      Hex Values                                 ASCII\n");
    printf("-------------------------------------------------------------\n");

    out = fopen("report.txt", "a");

    if (out != NULL)
    {
        time(&t);

        fprintf(out,
                "\n=====================================================\n");
        fprintf(out,
                "HEX DUMP REPORT\n");
        fprintf(out,
                "Time: %s",
                ctime(&t));
        fprintf(out,
                "=====================================================\n");
        fprintf(out,
                "Offset      Hex Values                                 ASCII\n");
        fprintf(out,
                "-------------------------------------------------------------\n");
    }

    while ((bytesRead =
            fread(buffer, 1, 16, fp)) > 0
           && offset < 128)
    {
        printf("%08X    ", offset);

        if (out != NULL)
        {
            fprintf(out,
                    "%08X    ",
                    offset);
        }

        /* Print Hex Values */
        for (int i = 0; i < 16; i++)
        {
            if (i < bytesRead)
            {
                printf("%02X ",
                       buffer[i]);

                if (out != NULL)
                {
                    fprintf(out,
                            "%02X ",
                            buffer[i]);
                }
            }
            else
            {
                printf("   ");

                if (out != NULL)
                {
                    fprintf(out,
                            "   ");
                }
            }
        }

        printf("   ");

        if (out != NULL)
        {
            fprintf(out,
                    "   ");
        }

        /* Print ASCII */
        for (int i = 0;
             i < bytesRead;
             i++)
        {
            if (isprint(buffer[i]))
            {
                printf("%c",
                       buffer[i]);

                if (out != NULL)
                {
                    fprintf(out,
                            "%c",
                            buffer[i]);
                }
            }
            else
            {
                printf(".");

                if (out != NULL)
                {
                    fprintf(out,
                            ".");
                }
            }
        }

        printf("\n");

        if (out != NULL)
        {
            fprintf(out,
                    "\n");
        }

        offset += bytesRead;
    }

    if (out != NULL)
    {
        fclose(out);
    }

    fclose(fp);
}