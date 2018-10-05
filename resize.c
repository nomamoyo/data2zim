#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "bmp.h"


int main(int argc, char *argv[])
{
    // check if user provided 3 command line arguments
    if (argc != 4)
    {
        // print error and end program if user provided more or less than 3 arguments
        printf("Enter scaling factor, original filename, and new filename in command line.\n");
        // error 1 means wrong number of arguments
        return 1;
    }
    // check that first value is integer between 0 and 100
    for (int dig = 0; dig < strlen(argv[1]); dig++)
    {
        // if you come across a non-digit print error and end program
        if (isdigit(argv[1][dig] == 0))
        {
            printf("Enter scaling factor between 0 and 100\n");
            // error 2 means argv[1] has non-digits
            return 2;
        }
    }

    //convert argv[1] into a resizing integer called scalefactor
    int scalefactor = atoi(argv[1]);

    // check that scaling factor is between 0 and 100, or print error
    if (scalefactor < 0 || scalefactor > 100)
    {
        printf("Enter scaling factor between 0 and 100\n");
        //error 3 means argv[1] is not between 0 and 100
        return 3;
    }

    // store input and output file names
    char *original = argv[2];
    char *final = argv[3];

    // open original bmp file in reading mode and give error if file is missing/corrupt
    FILE *input = fopen(original, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", original);
        // error 4 is for unreadable/missing original file
        return 4;
    }

    // open output file and if you can't write files into directory, close input file
    FILE *output = fopen(final, "w");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not create %s.\n", final);
        // error 5 is associated with writing permissions
        return 5;
    }

    // declare input BITMAPFILEHEADER as old_fh, and read it in
    BITMAPFILEHEADER old_fh;
    fread(&old_fh, sizeof(BITMAPFILEHEADER), 1, input);

    // declare input BITMAPinfoHEADER as old_if, and read it in
    BITMAPINFOHEADER old_ih;
    fread(&old_ih, sizeof(BITMAPINFOHEADER), 1, input);

    // ensure original is (likely) a 24-bit uncompressed BMP 4.0
    if (old_fh.bfType != 0x4d42 || old_fh.bfOffBits != 54 || old_ih.biSize != 40 ||
        old_ih.biBitCount != 24 || old_ih.biCompression != 0)
    {
        // if original is not a 24-bit bmp file, close input and output files and warn user
        fclose(output);
        fclose(input);
        // error 6 is for unsupported original file format
        printf("Unsupported file format.\n");
        return 6;
    }

    // declare output BITMAPFILEHEADER as new_fh, and just copy old_fh
    BITMAPFILEHEADER new_fh = old_fh;

    // declare output BITMAPINFOHEADER as new_ih, and just copy old_ih
    BITMAPINFOHEADER new_ih = old_ih;

    // resize biHeight and biWidth in new_ih
    new_ih.biHeight = old_ih.biHeight * scalefactor;
    new_ih.biWidth = old_ih.biWidth * scalefactor;

    // store old padding for reading input file later
    int old_padding = (4 - (old_ih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // define padding based on new_ih.biWidth 4 - (sizeof(new_ih.biWidth) % 4) does the wrong thing
    // if there's no remainder so I add a second %4 outside the entire formula to make
    // remainder 0 = 0 and keep other remainders as is
    int new_padding = (4 - (new_ih.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // resize the image: biWidth and biHeight are in pixels and to avoid negatives (for down-top)
    // we use abs() biSizeImage is in bytes, so we need to multiply width and height by 3, i.e.,
    // sizeof(RGBTRIPLE); padding is already in bytes
    new_ih.biSizeImage = (new_ih.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(new_ih.biHeight);

    // resize file size bfSize is biSizeImage + file and info headers, so BITMAPFILEHEADER = 40 + BITMAPINFOHEADER = 14
    new_fh.bfSize = new_ih.biSizeImage + 54;

    // write BITMAPFILEHEADER new_fh to output file
    fwrite(&new_fh, sizeof(BITMAPFILEHEADER), 1, output);

    // write BITMAPINFOHEADER new_ih to output file
    fwrite(&new_ih, sizeof(BITMAPINFOHEADER), 1, output);

    // iterate over entire scanlines a.k.a rows of pixels in the input file
    for (int row = 0; row < abs(old_ih.biHeight); row++)
    {
        // iterate downwards row by row
        for (int down = 0; down < scalefactor; down++)
        {
            // read each row pixel by pixel in the input file
            for (int pixy = 0; pixy < old_ih.biWidth; pixy++)
            {
                // declare temporary storage for each pixel read
                RGBTRIPLE pixel;
                // read pixel from input and store it in "pixel"
                fread(&pixel, sizeof(RGBTRIPLE), 1, input);

                // now write each row, pixel by pixel from left to right "scalefactor times"
                for (int across = 0; across < scalefactor; across++)
                {
                    // write pixel that was just read to output and repeat "scalefactor times"
                    fwrite(&pixel, sizeof(RGBTRIPLE), 1, output);
                }
            }
            // pixel writing is complete and I want to add my new_padding
            for (int k = 0; k < new_padding; k++)
            {
                // write the padding values
                fputc(0x00, output);
            }
            // done with row pixels, now let's skip over old_padding, and move to next row
            // from my understanding, fread() cannot read padding, so the pointer is currently at the end
            // of the last pixel along old_hi.biWidth, so I just need to skip teh padding to get to
            // the new row, but somehow, I'm not getting it right. I'll come get help.
            // I've spent at least
            fseek(input, old_padding, SEEK_CUR);
        }
    }
    // free memory
    fclose(input);
    fclose(output);
    // success
    return 0;
}