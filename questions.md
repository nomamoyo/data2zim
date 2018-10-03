# Questions

## What's `stdint.h`?
stdint.h is a library with functions that allow us to define the exact lengths of various header file data types e.g. BYTE and DWORD, using integer values. 

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?
These are integer data types and they define the maximum number of bits within a variable, for example uint8_t comprises 8 bits while int32_t comprises 32 bits.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?
1, 4, 4, and 2 bytes, respectively

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."
The first two bytes must be B and M, so 066 and 077 in ASCII decimal or 0x42 and 0x4d in hexadecimal.

## What's the difference between `bfSize` and `biSize`?
bfSize is the size of a bitmap file expressed in bytes. biSize is the number of bytes required in the BITMAPINFOHEADER structure (based on https://msdn.microsoft.com/en-us/library/dd183376(v=vs.85).aspx).

## What does it mean if `biHeight` is negative?
If biHeight is negative, then the bitmap is organized from the top-down, and the first byte translates into the upperleft corner of the image.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?
biBitCount specifies the number of bits per pixel.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?
fopen in line 24 will return NULL if the input (renamed infile in the code) is missing from the directory you are currently working in, or if you don't have user permissions to open that file. fopen in line 32 will return NULL if you don't have permissions to  write in the file or write any files (i.e. the outfile) to the directory you are working in.

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)
According to the manual, fread takes in four arguments, and the third is the total number of chunks that we want the program to read. In this case we want the program to only read one chunk, and in each instance, we have specified the chunk we want read using the third argument in fread.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?
Zero

## What does `fseek` do?
As the program reads the file, you can use fseek to move the pointer position by the number of bytes specified in the second argument of fseek(), from a location specified in the third argument of fseek().

## What is `SEEK_CUR`?
SEEK_CUR is the current position of the file pointer.
