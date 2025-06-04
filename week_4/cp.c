#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb"); //read in binary
    FILE *dst = fopen(argv[2], "wb"); //write in binary

    BYTE b;

    while (fread(&b, sizeof(b), 1, src) != 0) // while this statement is true, meaning while in the source there are still bytes, with the size of a byte (it could be one, but just in case), 1 byte at a time, we will do the following
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}
