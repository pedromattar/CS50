#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)//provides the correct usage for the user.
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }
    //variables declaration ( arrays to allocate memory for the content that we are going to read)
    unsigned char bufferr[512];
    unsigned char buffer[512];
    char filename[512];
    int i = 0;
    FILE *img = NULL;
    while (fread(buffer, 512, 1, file) == 1)//m check if theres a chunck of 512 bytes to get read or not
    {
        //fread(buffer, 512, 1, file);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if there is a new JPEG

            // FILE *img = fopen(filename, "w");
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                i++;

            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);

                i++;
            }

        }
        else if (i > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
}
