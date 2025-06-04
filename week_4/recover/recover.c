#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image name]\n");
        return 1;
    }

    // read the file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // im creating an array of bytes with the size of 512 bytes, so that im iterating through the
    // bytes 512 at a time
    BYTE buffer[BLOCK_SIZE];
    // we will need a counter to then later asign the names based on the total number of files
    // recovered
    int file_counter = 0;
    char filename[8]; // To store filenames like "000.jpg". 8 char (7 + null terminator)
    // we can't open it if it doesnt exist, so this way we are creating a pointer to it to then
    // later open it
    FILE *outptr = NULL;

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE,
                 inptr)) // while there are still bytes in the input, we will iterate through it in
                         // blocks of 512 bytes, and we will store them in the buffer
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        // f0 is 11110000 and e0 is 11100000. The & operator is comparing the bits in binary, and it
        // will return 1 only when there are 2 1's. So thats why we expect a result of 1110 when the
        // comparison is done to check that the byte starts with 0xe (1110)
        {
            // if the output is not null we will close it (so if its opern)
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            // the 03 means that the number should be at least 3 digits long, and it will be padded
            // with 0's. If we only used a '3' it would pad it with spaces. Also, the placeholder is
            // for a decimal integer (d) instead of a normal integer (i)
            sprintf(filename, "%03d.jpg", file_counter);

            outptr = fopen(filename, "w");

            // we put the counter here so that the first file is named with the 0 (as we started the
            // int variable)
            file_counter++;
        }
        // after we checked the if condition, and if we detected a jpg header, and efectively opened
        // a new file with its filname (in outptr), we will then write that information (buffer) to
        // the opened file how will we keep adding the buffer until we find a new header? after it
        // checks for the header and doesnt find it since we still have an open outptr (not NULL),
        // it will append the new buffer (continuation of the jpeg, because it doesnt have a new
        // header). In this case the header is alined with the start of the byte chunks, it can span
        // though several ones, but then if it ends mid-chunk it will be padded with 0's
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);

    return 0;
}
