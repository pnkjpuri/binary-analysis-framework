#include <stdio.h>
#include <time.h>
#include "framework.h"

void fileInfo(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        printf("[ERROR] Cannot open: %s\n", filename);
        return;
    }

    unsigned char sig[4] = {0};
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    fread(sig, 1, 4, fp);

    printf("\n--- FILE INFORMATION ---\n");
    printf("Name: %s\nSize: %ld bytes\nSignature: %02X %02X %02X %02X\n", filename, size, sig[0], sig[1], sig[2], sig[3]);

    if (sig[0] == 'M' && sig[1] == 'Z')
        printf("Type: Windows EXE\n");
    else if (sig[0] == 0x7F && sig[1] == 'E' && sig[2] == 'L' && sig[3] == 'F')
        printf("Type: Linux ELF\n");
    else if (sig[0] == 0x89 && sig[1] == 'P')
        printf("Type: PNG Image\n");
    else if (sig[0] == 0x25 && sig[1] == 0x50)
        printf("Type: PDF Document\n");
    else
        printf("Type: Unknown Format\n");

    fclose(fp);
}
