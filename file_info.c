#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "framework.h"

void fileInfo(const char *filename)
{
    FILE *fp;
    unsigned char sig[8] = {0};
    long size;

    char extension[20] = "Unknown";
    char finalType[100] = "Unknown File";
    char *ext;

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("\n[ERROR] Cannot open: %s\n",
               filename);
        return;
    }

    /* File Size */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    /* Read signature bytes */
    fread(sig, 1, 8, fp);

    /* ----------------------------
       EXTENSION DETECTION
    ----------------------------- */

    ext = strrchr(filename, '.');

    if (ext != NULL)
    {
        ext++;

        for (int i = 0; ext[i]; i++)
        {
            extension[i] =
                tolower(ext[i]);

            extension[i + 1] = '\0';
        }
    }

    /* ----------------------------
       SIGNATURE DETECTION
    ----------------------------- */

    if (sig[0] == 'M' &&
        sig[1] == 'Z')
    {
        strcpy(finalType,
               "Windows Executable (EXE/DLL)");
    }

    else if (sig[0] == 0x7F &&
             sig[1] == 'E' &&
             sig[2] == 'L' &&
             sig[3] == 'F')
    {
        strcpy(finalType,
               "Linux ELF Executable");
    }

    else if (sig[0] == 0x89 &&
             sig[1] == 'P' &&
             sig[2] == 'N' &&
             sig[3] == 'G')
    {
        strcpy(finalType,
               "PNG Image");
    }

    else if (sig[0] == 0xFF &&
             sig[1] == 0xD8)
    {
        strcpy(finalType,
               "JPEG Image");
    }

    else if (sig[0] == 0x25 &&
             sig[1] == 0x50 &&
             sig[2] == 0x44 &&
             sig[3] == 0x46)
    {
        strcpy(finalType,
               "PDF Document");
    }

    else if (sig[0] == 'P' &&
             sig[1] == 'K')
    {
        /* ZIP based files */
        if (strcmp(extension, "docx") == 0)
        {
            strcpy(finalType,
                   "Microsoft Word Document");
        }
        else if (strcmp(extension, "xlsx") == 0)
        {
            strcpy(finalType,
                   "Excel Spreadsheet");
        }
        else if (strcmp(extension, "pptx") == 0)
        {
            strcpy(finalType,
                   "PowerPoint Presentation");
        }
        else
        {
            strcpy(finalType,
                   "ZIP Archive");
        }
    }

    else if (sig[0] == 'R' &&
             sig[1] == 'a' &&
             sig[2] == 'r')
    {
        strcpy(finalType,
               "RAR Archive");
    }

    else
    {
        /* Extension fallback */

        if (strcmp(extension, "txt") == 0)
            strcpy(finalType, "Text File");

        else if (strcmp(extension, "csv") == 0)
            strcpy(finalType, "CSV File");

        else if (strcmp(extension, "json") == 0)
            strcpy(finalType, "JSON File");

        else if (strcmp(extension, "xml") == 0)
            strcpy(finalType, "XML File");

        else if (strcmp(extension, "html") == 0)
            strcpy(finalType, "HTML File");

        else if (strcmp(extension, "c") == 0)
            strcpy(finalType, "C Source File");

        else if (strcmp(extension, "cpp") == 0)
            strcpy(finalType, "C++ Source File");

        else if (strcmp(extension, "py") == 0)
            strcpy(finalType, "Python Source File");

        else if (strcmp(extension, "java") == 0)
            strcpy(finalType, "Java Source File");

        else if (strcmp(extension, "mp3") == 0)
            strcpy(finalType, "MP3 Audio File");

        else if (strcmp(extension, "mp4") == 0)
            strcpy(finalType, "MP4 Video File");

        else
            strcpy(finalType,
                   "Unknown File");
    }

    /* ----------------------------
       DISPLAY
    ----------------------------- */

    printf("\n=========================================\n");
    printf("           FILE INFORMATION\n");
    printf("=========================================\n");

    printf("File Name       : %s\n",
           filename);

    printf("File Size       : %ld bytes\n",
           size);

    printf("Extension Type  : %s\n",
           extension);

    printf("Signature       : %02X %02X %02X %02X\n",
           sig[0],
           sig[1],
           sig[2],
           sig[3]);

    printf("Detected Type   : %s\n",
           finalType);

    printf("=========================================\n");

    fclose(fp);
}
