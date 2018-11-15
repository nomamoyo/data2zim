#include <stdio.h>
#include <stdint.h>

// used char * instead of string and didn't include cs50.h
int main(int argc, char *argv[])
{
    // check if user provided an extension after the program name, otherwise return 1
    if (argc != 2)
    {
        printf("Provide file path\n");
        return 1;
    }

    // save argv[1] as my_file
    char *my_file = argv[1];

    // open my_file
    FILE *input = fopen(my_file, "r");

    // make sure file opens otherwise return 0
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 0;
    }

    // define byte
    typedef uint8_t  BYTE;

    // at most, I need to read only the first 4 bytes of each input file, so I'll define 'buffer' as 4 bytes
    BYTE buffer[4];

    // start reading one byte at a time and read only 4 bytes
    fread(buffer, 1, 4, input);

    // check for BMP
    if (buffer[0] == 0x42 && buffer[1] == 0x4d)
    {
      printf("BMP\n");
    }
    // check for PDF
    else if (buffer[0] == 0x25 && buffer[1] == 0x50 && buffer[2] == 0x44 && buffer[3] == 0x46)
    {
        printf("PDF\n");
    }
    // check for jpeg per Zamyla's code
    else if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
      printf("JPEG\n");
    }
    else
    {
        printf("\n");
    }
    // free memory
    fclose(input);
}