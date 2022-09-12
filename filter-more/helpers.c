#include "helpers.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)//for each row
    {
        for (int j = 0; j < width; j++)//for each column
        {
            int color = (((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) + 1.5) / 3);
            image[i][j].rgbtRed = color;
            image[i][j].rgbtGreen = color;
            image[i][j].rgbtBlue = color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)//for each row
    {
        for (int j = 0; j < (width / 2); j++)//for each column
        {
            int colorRed = image[i][width - j - 1].rgbtRed;
            int colorGreen = image[i][ width - j - 1].rgbtGreen;
            int colorBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = image[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = image[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = image[i][j].rgbtBlue;


            image[i][j].rgbtRed = colorRed;
            image[i][j].rgbtGreen = colorGreen;
            image[i][j].rgbtBlue = colorBlue;

        }
    }

    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i_init = -1;
    int i_end = 1;
    int j_init = -1;
    int j_end = 1;
    int done = 0;

    for (int i = 1; i < (height - 1) ; i++)//for each row
    {
        for (int j = 1; j < (width - 1); j++)//for each column
        {
            if (i == 0 && j == 0)
            {
                int colorRed = 0;
                int colorGreen = 0;
                int colorBlue = 0;
                for (int aux = 0; aux <= 1; aux++)
                {
                    for (int aux2 = 0 ; aux2 <= 1; aux2 ++)//for each pixel in the grid
                    {
                        colorRed += image[i + aux][j + aux2].rgbtRed;
                        colorGreen += image[i + aux][j + aux2].rgbtGreen;
                        colorBlue += image[i + aux][j + aux2].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = (colorRed / 4);
                image[i][j].rgbtGreen = (colorGreen / 4);
                image[i][j].rgbtBlue = (colorBlue / 4);
                done = 1;
            }
            if (i == 0 && j == (width - 1))
            {
                int colorRed = 0;
                int colorGreen = 0;
                int colorBlue = 0;
                for (int aux = 0; aux <= 1; aux++)
                {
                    for (int aux2 = -1 ; aux2 <= 0; aux2 ++)//for each pixel in the grid
                    {
                        colorRed += image[i + aux][j + aux2].rgbtRed;
                        colorGreen += image[i + aux][j + aux2].rgbtGreen;
                        colorBlue += image[i + aux][j + aux2].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = (colorRed / 4);
                image[i][j].rgbtGreen = (colorGreen / 4);
                image[i][j].rgbtBlue = (colorBlue / 4);
                done = 1;
            }
            if (i == (height - 1) && (j == 0))
            {
                int colorRed = 0;
                int colorGreen = 0;
                int colorBlue = 0;
                for (int aux = -1; aux <= 0; aux++)
                {
                    for (int aux2 = 0 ; aux2 <= 1; aux2 ++)//for each pixel in the grid
                    {
                        colorRed += image[i + aux][j + aux2].rgbtRed;
                        colorGreen += image[i + aux][j + aux2].rgbtGreen;
                        colorBlue += image[i + aux][j + aux2].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = (colorRed / 4);
                image[i][j].rgbtGreen = (colorGreen / 4);
                image[i][j].rgbtBlue = (colorBlue / 4);
                done = 1;
            }
            if ((i == width) && j == (height - 1))
            {
                int colorRed = 0;
                int colorGreen = 0;
                int colorBlue = 0;
                for (int aux = -1; aux <= 0; aux++)
                {
                    for (int aux2 = -1 ; aux2 <= 0; aux2 ++)//for each pixel in the grid
                    {
                        colorRed += image[i + aux][j + aux2].rgbtRed;
                        colorGreen += image[i + aux][j + aux2].rgbtGreen;
                        colorBlue += image[i + aux][j + aux2].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = (colorRed / 4);
                image[i][j].rgbtGreen = (colorGreen / 4);
                image[i][j].rgbtBlue = (colorBlue / 4);
                done = 1;
            }
            //                      ----------------- sides ----------------


            //   _---------------------------- 99% of the grid ---------------------------
            if (done == 0)
            {
                int colorRed = 0;
                int colorGreen = 0;
                int colorBlue = 0;
                for ( i_init = -1 ; i_init <= i_end; i_init++)
                {
                    for (  j_init = -1; j_init <= j_end; j_init ++)//for each pixel in the grid
                    {
                        colorRed += image[i + i_init][j + j_init].rgbtRed;
                        colorGreen += image[i + i_init][j + j_init].rgbtGreen;
                        colorBlue += image[i + i_init][j + j_init].rgbtBlue;
                    }
                }
                image[i][j].rgbtRed = (colorRed / 9)+1;
                image[i][j].rgbtGreen = (colorGreen / 9);
                image[i][j].rgbtBlue = (colorBlue / 9);
            }
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 1; i < (height - 1) ; i++)
    {
        for (int j = 1; j < (width - 1); j++)
        {

        }
    }
    return;
}
