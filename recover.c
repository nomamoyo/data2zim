#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

// copy pasted bmp.h code
// aliases for C/C++ primitive data types
// https://msdn.microsoft.com/en-us/library/cc230309.aspx
typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

// information about the type, size, and layout of a file
// https://msdn.microsoft.com/en-us/library/dd183374(v=vs.85).aspx
typedef struct
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} __attribute__((__packed__))
BITMAPFILEHEADER;

// information about the dimensions and color format
// https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx
typedef struct
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} __attribute__((__packed__))
BITMAPINFOHEADER;

// relative intensities of red, green, and blue
// https://msdn.microsoft.com/en-us/library/dd162939(v=vs.85).aspx
typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;


int main(int argc, char *argv[])
{
    //check if user provided only one command line argument
    if (argc != 2)
    {
        //print error and end program if user provided more or less than 1 argument
        printf("Provide filename in command line.\n");
        //error 1 means wrong number of arguments
        return 1;
    }
    //store card.raw name as "raw"
    char *raw = argv[1];

    // open card.raw, read it, and store it as "card"
    FILE *card = fopen(raw, "r");

    //check if card was opened and read
    if (card == NULL)
    {
        //print error message and end program
        fprintf(stderr, "Could not open %s.\n", raw);
        //error 1 means file is missing or not readable
        return 2;
    }

    // define chunks of 512 bytes
    BYTE chunk[512];

    // declare file called img
    FILE *img = NULL;

    //define new jpg file
    char filename[8];

    // declare filecounter to go from jpeg to jpeg
    int counter = 0;

    // declare boolean variable to check if we're at the start of a jpeg and set it as false first
    bool first_one = false;

    // while you're in card.raw file, read one 512 byte chunk at a time until you get to the end, 0x00
    while (fread(chunk, 1, 512, card) != 0x00)
    {
        //if you find a jpeg header sequence as provided in the walkthrough
        if (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff && (chunk[3] & 0xf0) == 0xe0)
        {
            // check if we're at the start of the first jpeg
            if (!first_one)
            {
                // since we just started reading card, if jpeg seq is there, it is the first one
                // so change boolean to true value
                first_one = true;

                // create jpeg file
                sprintf(filename, "%03i.jpg", counter++);

                // open new jpeg file "img" to write in it
                img = fopen(filename, "w");

                // check for file writing errors
                if (img == NULL)
                {
                    //error 3 means user couldn't write photo - no permissions?
                    fprintf(stderr, "Could not write file.");
                    return 3;
                }
                //copy 512 bytes from card.raw into new file called img
                fwrite(chunk, 1, 512, img);
            }
            // if we haven't found our jpeg
            else
            {
                // free memory and continue to the next 512 bytes
                fclose(img);

                // create new jpeg file
                sprintf(filename, "%03i.jpg", counter++);

                // open new jpeg file "img" to write in it
                img = fopen(filename, "w");

                // check for file writing/creation errors
                if (img == NULL)
                {
                    //error 3 means user couldn't write photo - no permissions?
                    fprintf(stderr, "Could not write file.");
                    return 3;
                }
                //copy 512 bytes from card.raw into new file called img
                fwrite(chunk, 1, 512, img);
            }
        }
        // if we're already inside our first jpeg
        else
        {
            if (first_one)
            {
                //copy 512 bytes from card.raw into new file called img
                fwrite(chunk, 1, 512, img);
            }
        }
    }
    //free memory and return zero for success
    fclose(img);
    fclose(card);
    return 0;
}

